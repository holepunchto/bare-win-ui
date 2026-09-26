#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_input_system_cursor_create(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  int32_t shape;
  if (!bare_win_ui__read_int32(env, argv[0], "shape", &shape)) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(
      env,
      InputSystemCursor::Create(static_cast<InputSystemCursorShape>(shape))
    );
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_input_system_cursor_cursor_shape(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  InputSystemCursor cursor = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &cursor) < 0) return nullptr;

  js_value_t *result;

  try {
    err = js_create_int32(env, static_cast<int32_t>(cursor.CursorShape()), &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
