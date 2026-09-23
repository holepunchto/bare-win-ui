#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_composition_shape_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  CompositionShape shape = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shape) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, shape.Offset());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      shape.Offset({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
