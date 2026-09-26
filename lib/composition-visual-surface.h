#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_composition_visual_surface_source_visual(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CompositionVisualSurface surface = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &surface) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, surface.SourceVisual());
    } else {
      Visual visual = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "visual", &visual)) return nullptr;

      surface.SourceVisual(visual);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_visual_surface_source_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  CompositionVisualSurface surface = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &surface) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, surface.SourceSize());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      surface.SourceSize({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_visual_surface_source_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  CompositionVisualSurface surface = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &surface) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, surface.SourceOffset());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      surface.SourceOffset({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
