#include <atomic>
#include <thread>

#include <assert.h>
#include <bare.h>
#include <io.h>
#include <js.h>
#include <log.h>
#include <path.h>
#include <rlimit.h>
#include <uv.h>

#include "bootstrap.h"
#include "windows-app-sdk.h"

static uv_barrier_t bare__platform_ready;
static uv_async_t bare__platform_shutdown;
static uv_thread_t bare__platform_thread;
static js_platform_t *bare__platform;

static int bare__argc;
static char **bare__argv;

static uv_loop_t *bare__loop;
static uv_async_t bare__shutdown;
static bare_t *bare;

static DispatcherQueue bare__dispatcher = nullptr;
static std::atomic<bool> bare__dispatch_pending = false;
static std::atomic<bool> bare__running = true;
static std::thread bare__poller;

static void
bare__on_shutdown(uv_async_t *handle) {
  uv_close((uv_handle_t *) handle, nullptr);
}

static void
bare__on_platform_thread(void *data) {
  int err;

  uv_loop_t loop;
  err = uv_loop_init(&loop);
  assert(err == 0);

  err = uv_async_init(&loop, &bare__platform_shutdown, bare__on_shutdown);
  assert(err == 0);

  err = js_create_platform(&loop, nullptr, &bare__platform);
  assert(err == 0);

  uv_barrier_wait(&bare__platform_ready);

  err = uv_run(&loop, UV_RUN_DEFAULT);
  assert(err == 0);

  err = js_destroy_platform(bare__platform);
  assert(err == 0);

  err = uv_run(&loop, UV_RUN_DEFAULT);
  assert(err == 0);

  err = uv_loop_close(&loop);
  assert(err == 0);
}

static void
bare__on_poller_thread(void) {
  while (bare__running) {
    DWORD bytes;
    ULONG_PTR key;
    OVERLAPPED *overlapped;

    GetQueuedCompletionStatus(
      bare__loop->iocp,
      &bytes,
      &key,
      &overlapped,
      uv_backend_timeout(bare__loop)
    );

    if (!bare__running) break;

    if (overlapped != nullptr) {
      PostQueuedCompletionStatus(bare__loop->iocp, bytes, key, overlapped);
    }

    bool expected = false;

    if (bare__dispatch_pending.compare_exchange_strong(expected, true)) {
      bare__dispatcher.TryEnqueue([]() {
        int err;

        bare__dispatch_pending = false;

        err = bare_run(bare, UV_RUN_NOWAIT);
        assert(err >= 0);
      });
    }
  }
}

static void
bare__terminate(void) {
  int err;

  PostQueuedCompletionStatus(bare__loop->iocp, 0, 0, nullptr);

  bare__poller.join();

  err = uv_async_send(&bare__shutdown);
  assert(err == 0);

  err = bare_terminate(bare);
  assert(err == 0);

  err = bare_run(bare, UV_RUN_DEFAULT);
  assert(err == 0);

  err = bare_teardown(bare, UV_RUN_DEFAULT, nullptr);
  assert(err == 0);

  err = uv_loop_close(bare__loop);
  assert(err == 0);

  err = uv_async_send(&bare__platform_shutdown);
  assert(err == 0);

  uv_thread_join(&bare__platform_thread);

  err = log_close();
  assert(err == 0);
}

static void
bare__launch() {
  int err;

  err = uv_barrier_init(&bare__platform_ready, 2);
  assert(err == 0);

  err = uv_thread_create(&bare__platform_thread, bare__on_platform_thread, nullptr);
  assert(err == 0);

  uv_barrier_wait(&bare__platform_ready);

  uv_barrier_destroy(&bare__platform_ready);

  bare__loop = uv_default_loop();

  err = uv_async_init(bare__loop, &bare__shutdown, bare__on_shutdown);
  assert(err == 0);

  err = bare_setup(bare__loop, bare__platform, nullptr, bare__argc, (const char **) bare__argv, nullptr, &bare);
  assert(err == 0);

  size_t len;

  char bin[4096];
  len = sizeof(bin);

  err = uv_exepath(bin, &len);
  assert(err == 0);

  size_t dir;
  err = path_dirname(bin, &dir, path_behavior_system);
  assert(err == 0);

  char bundle[4096];
  len = 4096;

  err = path_join(
    (const char *[]) {bin, "..", "..", "Resources", "app.bundle", NULL},
    bundle,
    &len,
    path_behavior_system
  );
  assert(err == 0);

  err = bare_load(bare, bundle, nullptr, nullptr);
  (void) err;

  bare__dispatcher = DispatcherQueue::GetForCurrentThread();

  bare__dispatcher.ShutdownCompleted([=](const auto &, const auto &) {
    bare__terminate();
  });

  bare__poller = std::thread([]() {
    bare__on_poller_thread();
  });
}

struct BareApp : public ApplicationT<BareApp> {
  void
  OnLaunched(LaunchActivatedEventArgs const &) {
    bare__launch();
  }
};

int
main(int argc, char *argv[]) {
  int err;

  err = log_open("bare", 0);
  assert(err == 0);

  err = rlimit_set(rlimit_open_files, rlimit_infer);
  assert(err == 0);

  argv = uv_setup_args(argc, argv);

  bare__argc = argc;
  bare__argv = argv;

  bare__try_bootstrap_runtime();

  freopen("NUL", "r", stdin);
  freopen("NUL", "w", stdout);
  freopen("NUL", "w", stderr);

  init_apartment();

  Application::Start([=](auto &&) { make<BareApp>(); });

  return 0;
}
