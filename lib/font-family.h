#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_font_family_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  hstring family_name;
  if (!bare_win_ui__read_string(env, argv[0], "family_name", &family_name)) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, FontFamily(family_name));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_font_family_source(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  FontFamily font_family = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &font_family) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_string(env, font_family.Source());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
