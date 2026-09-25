#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_progress_ring_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, ProgressRing());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_progress_ring_is_active(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  ProgressRing ring = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &ring) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_boolean(env, ring.IsActive());
    } else {
      bool value;
      if (!bare_win_ui__read_bool(env, argv[1], "isActive", &value)) return nullptr;

      ring.IsActive(value);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
