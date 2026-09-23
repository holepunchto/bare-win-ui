#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_composition_rounded_rectangle_geometry_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  CompositionRoundedRectangleGeometry geometry = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &geometry) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, geometry.Size());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      geometry.Size({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static void
bare_win_ui_composition_rounded_rectangle_geometry_size_typed(js_value_t *receiver, uint32_t bare_tag, double x, double y, js_typed_callback_info_t *info) {
  auto geometry = bare_winrt__object(bare_tag).try_as<CompositionRoundedRectangleGeometry>();

  if (geometry == nullptr) return;

  try {
    geometry.Size({float(x), float(y)});
  } catch (hresult_error const &) {
  }
}

static js_value_t *
bare_win_ui_composition_rounded_rectangle_geometry_corner_radius(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  CompositionRoundedRectangleGeometry geometry = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &geometry) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, geometry.CornerRadius());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      geometry.CornerRadius({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_rounded_rectangle_geometry_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  CompositionRoundedRectangleGeometry geometry = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &geometry) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, geometry.Offset());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      geometry.Offset({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
