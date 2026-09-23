#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_compositor_create_shape_visual(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  Compositor compositor = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &compositor) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, compositor.CreateShapeVisual());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_compositor_create_rounded_rectangle_geometry(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  Compositor compositor = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &compositor) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, compositor.CreateRoundedRectangleGeometry());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_compositor_create_sprite_shape(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Compositor compositor = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &compositor) < 0) return nullptr;

  js_value_t *result;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, compositor.CreateSpriteShape());
    } else {
      CompositionGeometry geometry = nullptr;
      if (bare_winrt__read_type(env, argv[1], "geometry", &geometry) < 0) return nullptr;

      result = bare_win_ui__from_object(env, compositor.CreateSpriteShape(geometry));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_compositor_create_geometric_clip(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Compositor compositor = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &compositor) < 0) return nullptr;

  js_value_t *result;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, compositor.CreateGeometricClip());
    } else {
      CompositionGeometry geometry = nullptr;
      if (bare_winrt__read_type(env, argv[1], "geometry", &geometry) < 0) return nullptr;

      result = bare_win_ui__from_object(env, compositor.CreateGeometricClip(geometry));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_compositor_create_color_brush(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 5);

  Compositor compositor = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &compositor) < 0) return nullptr;

  js_value_t *result;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, compositor.CreateColorBrush());
    } else {
      uint8_t a;
      if (!bare_win_ui__read_byte(env, argv[1], "a", &a)) return nullptr;

      uint8_t r;
      if (!bare_win_ui__read_byte(env, argv[2], "r", &r)) return nullptr;

      uint8_t g;
      if (!bare_win_ui__read_byte(env, argv[3], "g", &g)) return nullptr;

      uint8_t b;
      if (!bare_win_ui__read_byte(env, argv[4], "b", &b)) return nullptr;

      result = bare_win_ui__from_object(env, compositor.CreateColorBrush({a, r, g, b}));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
