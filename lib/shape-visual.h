#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_shape_visual_shapes(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ShapeVisual visual = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &visual) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_object(env, visual.Shapes());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
