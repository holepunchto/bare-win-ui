#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_panel_children(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  Panel panel = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &panel) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_object(env, panel.Children());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_panel_background(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Panel panel = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &panel) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, panel.Background());
    } else {
      Brush background = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "background", &background)) return nullptr;

      panel.Background(background);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
