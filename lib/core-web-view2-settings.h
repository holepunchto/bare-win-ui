#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_core_web_view2_settings_are_dev_tools_enabled(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CoreWebView2Settings settings = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &settings) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_boolean(env, settings.AreDevToolsEnabled());
    } else {
      bool value;
      if (!bare_win_ui__read_bool(env, argv[1], "areDevToolsEnabled", &value)) return nullptr;

      settings.AreDevToolsEnabled(value);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
