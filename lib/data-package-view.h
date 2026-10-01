#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

// A view reads its text asynchronously, so the caller passes a callback.
struct bare_win_ui_data_package_view_read_t {
  js_env_t *env;
  js_ref_t *callback;
};

static void
bare_win_ui_data_package_view__on_read(bare_win_ui_data_package_view_read_t *read, const char *error, hstring const &text) {
  int err;

  auto env = read->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *callback;
  err = js_get_reference_value(env, read->callback, &callback);
  assert(err == 0);

  js_value_t *argv[2];

  if (error == nullptr) {
    err = js_get_null(env, &argv[0]);
    assert(err == 0);

    argv[1] = bare_win_ui__from_string(env, text);
  } else {
    err = js_create_string_utf8(env, reinterpret_cast<const utf8_t *>(error), size_t(-1), &argv[0]);
    assert(err == 0);

    err = js_get_null(env, &argv[1]);
    assert(err == 0);
  }

  js_value_t *receiver;
  err = js_get_null(env, &receiver);
  assert(err == 0);

  err = js_call_function(env, receiver, callback, 2, argv, nullptr);
  (void) err;

  err = js_delete_reference(env, read->callback);
  assert(err == 0);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);

  delete read;
}

static js_value_t *
bare_win_ui_data_package_view_contains(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  DataPackageView view = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &view) < 0) return nullptr;

  hstring format;
  if (!bare_win_ui__read_string(env, argv[1], "format", &format)) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_boolean(env, view.Contains(format));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_data_package_view_get_text_async(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  DataPackageView view = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &view) < 0) return nullptr;

  auto read = new bare_win_ui_data_package_view_read_t();

  read->env = env;

  err = js_create_reference(env, argv[1], 1, &read->callback);
  assert(err == 0);

  try {
    // The completion runs on a thread pool thread and the engine runs on the
    // dispatcher thread, so the answer is sent back there.
    auto dispatcher = DispatcherQueue::GetForCurrentThread();

    view.GetTextAsync().Completed([=](auto const &operation, AsyncStatus const status) {
      auto text = status == AsyncStatus::Completed ? operation.GetResults() : hstring();

      dispatcher.TryEnqueue([=] {
        bare_win_ui_data_package_view__on_read(
          read, status == AsyncStatus::Completed ? nullptr : "The text could not be read", text
        );
      });
    });
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  } catch (...) {
    bare_win_ui__throw(env, hresult_error(E_FAIL, L"The text could not be read"));

    return nullptr;
  }

  return nullptr;
}
