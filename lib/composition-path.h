#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

// A compositor cannot make a path itself. A path is built from a geometry
// source, and Win2D provides one.
static js_value_t *
bare_win_ui_composition_path_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  CanvasGeometry geometry = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &geometry) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, CompositionPath(geometry));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_path_geometry_path(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  CompositionPathGeometry geometry = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &geometry) < 0) return nullptr;

  CompositionPath path = nullptr;
  if (!bare_win_ui__read_nullable(env, state, argv[1], "path", &path)) return nullptr;

  try {
    geometry.Path(path);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
