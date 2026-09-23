#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_display_area_fallback_none = int(DisplayAreaFallback::None),
  bare_win_ui_display_area_fallback_primary = int(DisplayAreaFallback::Primary),
  bare_win_ui_display_area_fallback_nearest = int(DisplayAreaFallback::Nearest),
};

static js_value_t *
bare_win_ui_display_area_primary(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, DisplayArea::Primary());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_display_area_get_from_window_id(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  uint64_t id;
  bool lossless;
  err = js_get_value_bigint_uint64(env, argv[0], &id, &lossless);
  if (err < 0) return nullptr;

  int32_t fallback;
  if (!bare_win_ui__read_int32(env, argv[1], "fallback", &fallback)) return nullptr;

  js_value_t *result;

  try {
    auto area = DisplayArea::GetFromWindowId(WindowId{id}, DisplayAreaFallback(fallback));

    result = bare_win_ui__from_object(env, state, area);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

#define V(name, fn) \
  static js_value_t * \
  name(js_env_t *env, js_callback_info_t *info) { \
    int err; \
\
    size_t argc = 1; \
    js_value_t *argv[1]; \
\
    bare_win_ui_state_t *state; \
    err = js_get_callback_info(env, info, &argc, argv, nullptr, (void **) &state); \
    assert(err == 0); \
\
    assert(argc == 1); \
\
    DisplayArea area = nullptr; \
    if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &area) < 0) return nullptr; \
\
    js_value_t *result; \
\
    try { \
      auto value = area.fn(); \
\
      result = bare_win_ui__from_fields(env, {{"x", double(value.X)}, {"y", double(value.Y)}, {"width", double(value.Width)}, {"height", double(value.Height)}}); \
    } catch (hresult_error const &error) { \
      bare_win_ui__throw(env, error); \
\
      return nullptr; \
    } \
\
    return result; \
  }

V(bare_win_ui_display_area_outer_bounds, OuterBounds)
V(bare_win_ui_display_area_work_area, WorkArea)
#undef V

static js_value_t *
bare_win_ui_display_area_is_primary(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  DisplayArea area = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &area) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_boolean(env, area.IsPrimary());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
