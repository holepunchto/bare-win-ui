#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_xaml_root_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  js_value_t *result;

  try {
    auto size = root.Size();

    result = bare_win_ui__from_fields(env, {{"width", size.Width}, {"height", size.Height}});
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_xaml_root_rasterization_scale(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_double(env, root.RasterizationScale());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_xaml_root_is_host_visible(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_boolean(env, root.IsHostVisible());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
