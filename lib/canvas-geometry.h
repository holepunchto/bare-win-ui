#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

// A geometry is what a composition path is built from, and Win2D is what makes
// one. Nothing here draws with it: it crosses straight into a path.
static js_value_t *
bare_win_ui_canvas_geometry_create_path(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  CanvasPathBuilder builder = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &builder) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, CanvasGeometry::CreatePath(builder));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
