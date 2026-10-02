#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_general_transform_transform_point(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  GeneralTransform transform = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &transform) < 0) return nullptr;

  double x;
  if (!bare_win_ui__read_double(env, argv[1], "x", &x)) return nullptr;

  double y;
  if (!bare_win_ui__read_double(env, argv[2], "y", &y)) return nullptr;

  js_value_t *result;

  try {
    auto point = transform.TransformPoint({float(x), float(y)});

    result = bare_win_ui__from_point(env, point.X, point.Y);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_general_transform_transform_bounds(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 5);

  GeneralTransform transform = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &transform) < 0) return nullptr;

  double values[4];

  for (size_t i = 0; i < 4; i++) {
    if (!bare_win_ui__read_double(env, argv[i + 1], "bounds", &values[i])) return nullptr;
  }

  js_value_t *result;

  try {
    auto bounds = transform.TransformBounds(
      {float(values[0]), float(values[1]), float(values[2]), float(values[3])}
    );

    result = bare_win_ui__from_rect(env, bounds);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_general_transform_inverse(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  GeneralTransform transform = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &transform) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, transform.Inverse());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
