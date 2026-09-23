#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_sprite_visual_brush(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  SpriteVisual visual = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &visual) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, state, visual.Brush());
    } else {
      CompositionBrush brush = nullptr;
      if (!bare_win_ui__read_nullable(env, state, argv[1], "brush", &brush)) return nullptr;

      visual.Brush(brush);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_sprite_visual_shadow(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  SpriteVisual visual = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &visual) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, state, visual.Shadow());
    } else {
      CompositionShadow shadow = nullptr;
      if (!bare_win_ui__read_nullable(env, state, argv[1], "shadow", &shadow)) return nullptr;

      visual.Shadow(shadow);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
