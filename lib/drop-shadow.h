#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_drop_shadow_color(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 5);

  DropShadow shadow = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shadow) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_color(env, shadow.Color());
    } else {
      uint8_t a;
      if (!bare_win_ui__read_byte(env, argv[1], "a", &a)) return nullptr;

      uint8_t r;
      if (!bare_win_ui__read_byte(env, argv[2], "r", &r)) return nullptr;

      uint8_t g;
      if (!bare_win_ui__read_byte(env, argv[3], "g", &g)) return nullptr;

      uint8_t b;
      if (!bare_win_ui__read_byte(env, argv[4], "b", &b)) return nullptr;

      shadow.Color({a, r, g, b});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_drop_shadow_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 4;
  js_value_t *argv[4];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 4);

  DropShadow shadow = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shadow) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float3(env, shadow.Offset());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      float z;
      if (!bare_win_ui__read_float(env, argv[3], "z", &z)) return nullptr;

      shadow.Offset({x, y, z});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_drop_shadow_blur_radius(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  DropShadow shadow = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shadow) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      err = js_create_double(env, shadow.BlurRadius(), &result);
      assert(err == 0);
    } else {
      float blur_radius;
      if (!bare_win_ui__read_float(env, argv[1], "blur_radius", &blur_radius)) return nullptr;

      shadow.BlurRadius(blur_radius);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_drop_shadow_opacity(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  DropShadow shadow = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shadow) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      err = js_create_double(env, shadow.Opacity(), &result);
      assert(err == 0);
    } else {
      float opacity;
      if (!bare_win_ui__read_float(env, argv[1], "opacity", &opacity)) return nullptr;

      shadow.Opacity(opacity);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_drop_shadow_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  DropShadow shadow = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shadow) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, shadow.Mask());
    } else {
      CompositionBrush mask = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "mask", &mask)) return nullptr;

      shadow.Mask(mask);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
