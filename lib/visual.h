#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_visual_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  Visual visual = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &visual) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_float2(env, visual.Size());
    } else {
      float x;
      if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

      float y;
      if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

      visual.Size({x, y});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static void
bare_win_ui_visual_size_typed(js_value_t *receiver, uint32_t bare_tag, double x, double y, js_typed_callback_info_t *info) {
  auto visual = bare_winrt__object(bare_tag).try_as<Visual>();

  if (visual == nullptr) return;

  try {
    visual.Size({float(x), float(y)});
  } catch (hresult_error const &) {
  }
}

static js_value_t *
bare_win_ui_visual_clip(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Visual visual = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &visual) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, visual.Clip());
    } else {
      CompositionClip clip = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "clip", &clip)) return nullptr;

      visual.Clip(clip);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// A `float4x4` is sixteen numbers in the order CSS gives `matrix3d` its own,
// so it crosses as a flat list rather than an object of named fields.
#define BARE_WIN_UI_TRANSFORM(V) \
  V(0, m11) V(1, m12) V(2, m13) V(3, m14) \
  V(4, m21) V(5, m22) V(6, m23) V(7, m24) \
  V(8, m31) V(9, m32) V(10, m33) V(11, m34) \
  V(12, m41) V(13, m42) V(14, m43) V(15, m44)

static js_value_t *
bare_win_ui_visual_transform_matrix(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Visual visual = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &visual) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      auto matrix = visual.TransformMatrix();

      err = js_create_array_with_length(env, 16, &result);
      assert(err == 0);

#define V(index, field) \
  { \
    js_value_t *value; \
    err = js_create_double(env, matrix.field, &value); \
    assert(err == 0); \
    err = js_set_element(env, result, index, value); \
    assert(err == 0); \
  }
      BARE_WIN_UI_TRANSFORM(V)
#undef V
    } else {
      Numerics::float4x4 matrix;

#define V(index, field) \
  { \
    js_value_t *value; \
    err = js_get_element(env, argv[1], index, &value); \
    assert(err == 0); \
    if (!bare_win_ui__read_float(env, value, #field, &matrix.field)) return nullptr; \
  }
      BARE_WIN_UI_TRANSFORM(V)
#undef V

      visual.TransformMatrix(matrix);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
