#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_solid_color_brush_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 4;
  js_value_t *argv[4];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 0 || argc == 4);

  js_value_t *result;

  try {
    if (argc == 0) {
      result = bare_win_ui__from_object(env, SolidColorBrush());
    } else {
      uint8_t a;
      if (!bare_win_ui__read_byte(env, argv[0], "a", &a)) return nullptr;

      uint8_t r;
      if (!bare_win_ui__read_byte(env, argv[1], "r", &r)) return nullptr;

      uint8_t g;
      if (!bare_win_ui__read_byte(env, argv[2], "g", &g)) return nullptr;

      uint8_t b;
      if (!bare_win_ui__read_byte(env, argv[3], "b", &b)) return nullptr;

      result = bare_win_ui__from_object(env, SolidColorBrush({a, r, g, b}));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_solid_color_brush_color(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 5);

  SolidColorBrush brush = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &brush) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_color(env, brush.Color());
    } else {
      uint8_t a;
      if (!bare_win_ui__read_byte(env, argv[1], "a", &a)) return nullptr;

      uint8_t r;
      if (!bare_win_ui__read_byte(env, argv[2], "r", &r)) return nullptr;

      uint8_t g;
      if (!bare_win_ui__read_byte(env, argv[3], "g", &g)) return nullptr;

      uint8_t b;
      if (!bare_win_ui__read_byte(env, argv[4], "b", &b)) return nullptr;

      brush.Color({a, r, g, b});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
