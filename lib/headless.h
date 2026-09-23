#pragma once

#include <assert.h>
#include <js.h>
#include <string>
#include <uv.h>

#include "bootstrap.h"
#include "bridging.h"

// The preflight bundle loads before `Application::Start`, so the runtime marks
// itself with `bare_win_ui_runtime` rather than being detected by its dispatcher.
static thread_local DispatcherQueueController bare_win_ui__headless_dispatcher = nullptr;
static thread_local WindowsXamlManager bare_win_ui__headless_xaml = nullptr;

static thread_local uv_timer_t *bare_win_ui__headless_pump = nullptr;
static thread_local uint32_t bare_win_ui__headless_holds = 0;

static void
bare_win_ui__headless_hold() {
  if (bare_win_ui__headless_pump == nullptr) return;

  if (bare_win_ui__headless_holds++ == 0) uv_ref(reinterpret_cast<uv_handle_t *>(bare_win_ui__headless_pump));
}

static void
bare_win_ui__headless_release() {
  if (bare_win_ui__headless_pump == nullptr) return;

  if (--bare_win_ui__headless_holds == 0) uv_unref(reinterpret_cast<uv_handle_t *>(bare_win_ui__headless_pump));
}

static void
bare_win_ui__headless_on_pump(uv_timer_t *handle) {
  MSG msg;

  while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
}

static void
bare_win_ui__headless_on_close(uv_handle_t *handle) {
  delete reinterpret_cast<uv_timer_t *>(handle);
}

static void
bare_win_ui__headless_on_teardown(void *data) {
  bare_win_ui__headless_pump = nullptr;
  bare_win_ui__headless_holds = 0;

  uv_close(reinterpret_cast<uv_handle_t *>(data), bare_win_ui__headless_on_close);
}

static void
bare_win_ui__headless_search_prebuilds() {
  HMODULE self;
  GetModuleHandleExW(
    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
    reinterpret_cast<LPCWSTR>(&bare_win_ui__headless_search_prebuilds),
    &self
  );

  wchar_t path[MAX_PATH];
  auto len = GetModuleFileNameW(self, path, MAX_PATH);

  std::wstring dir(path, len);
  dir.resize(dir.find_last_of(L'\\'));

  SetDllDirectoryW((dir + L"\\bare").c_str());
}

static int
bare_win_ui__headless_init(js_env_t *env) {
  int err;

  if (GetProcAddress(GetModuleHandleW(nullptr), "bare_win_ui_runtime")) return 0;

  if (bare_win_ui__headless_dispatcher == nullptr) {
    // Match the runtime's manifest, or the system scales the window as a bitmap.
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    bare_win_ui__headless_search_prebuilds();

    if (bare__try_bootstrap_runtime() < 0) {
      err = js_throw_error(env, nullptr, "Could not bootstrap the Windows App SDK");
      assert(err == 0);

      return -1;
    }

    try {
      init_apartment(apartment_type::single_threaded);

      bare_win_ui__headless_dispatcher = DispatcherQueueController::CreateOnCurrentThread();
      bare_win_ui__headless_xaml = WindowsXamlManager::InitializeForCurrentThread();
    } catch (hresult_error const &error) {
      bare_win_ui__throw(env, error);

      return -1;
    }
  }

  uv_loop_t *loop;
  err = js_get_env_loop(env, &loop);
  assert(err == 0);

  auto timer = new uv_timer_t;

  err = uv_timer_init(loop, timer);
  assert(err == 0);

  err = uv_timer_start(timer, bare_win_ui__headless_on_pump, 0, 8);
  assert(err == 0);

  uv_unref(reinterpret_cast<uv_handle_t *>(timer));

  bare_win_ui__headless_pump = timer;

  err = js_add_teardown_callback(env, bare_win_ui__headless_on_teardown, timer);
  assert(err == 0);

  return 0;
}
