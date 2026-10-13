#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_content_island_environment_app_window_id(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  winrt::Microsoft::UI::Content::ContentIslandEnvironment environment = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &environment) < 0) return nullptr;

  js_value_t *result;

  try {
    err = js_create_bigint_uint64(env, environment.AppWindowId().Value, &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
