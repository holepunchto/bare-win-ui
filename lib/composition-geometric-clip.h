#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_composition_geometric_clip_geometry(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CompositionGeometricClip clip = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &clip) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, clip.Geometry());
    } else {
      CompositionGeometry geometry = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "geometry", &geometry)) return nullptr;

      clip.Geometry(geometry);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
