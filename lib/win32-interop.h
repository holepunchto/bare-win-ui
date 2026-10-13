#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_win32_interop_get_window_from_window_id(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  uint64_t id;
  bool lossless;
  err = js_get_value_bigint_uint64(env, argv[0], &id, &lossless);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_bigint_uint64(env, uint64_t(uintptr_t(GetWindowFromWindowId(WindowId{id}))), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui_win32_interop_get_window_id_from_window(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  uint64_t window;
  bool lossless;
  err = js_get_value_bigint_uint64(env, argv[0], &window, &lossless);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_bigint_uint64(env, GetWindowIdFromWindow(HWND(uintptr_t(window))).Value, &result);
  assert(err == 0);

  return result;
}
