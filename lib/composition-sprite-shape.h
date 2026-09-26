#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_composition_sprite_shape_geometry(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CompositionSpriteShape shape = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shape) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, shape.Geometry());
    } else {
      CompositionGeometry geometry = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "geometry", &geometry)) return nullptr;

      shape.Geometry(geometry);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_sprite_shape_fill_brush(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CompositionSpriteShape shape = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shape) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, shape.FillBrush());
    } else {
      CompositionBrush fill_brush = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "fill_brush", &fill_brush)) return nullptr;

      shape.FillBrush(fill_brush);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_sprite_shape_stroke_brush(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CompositionSpriteShape shape = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shape) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, shape.StrokeBrush());
    } else {
      CompositionBrush stroke_brush = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "stroke_brush", &stroke_brush)) return nullptr;

      shape.StrokeBrush(stroke_brush);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_sprite_shape_stroke_thickness(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  CompositionSpriteShape shape = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shape) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, shape.StrokeThickness());
    } else {
      float stroke_thickness;
      if (!bare_win_ui__read_float(env, argv[1], "stroke_thickness", &stroke_thickness)) return nullptr;

      shape.StrokeThickness(stroke_thickness);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_composition_sprite_shape_stroke_dash_array(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  CompositionSpriteShape shape = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &shape) < 0) return nullptr;

  try {
    auto dashes = shape.StrokeDashArray();

    dashes.Clear();

    uint32_t len;
    err = js_get_array_length(env, argv[1], &len);
    assert(err == 0);

    for (uint32_t i = 0; i < len; i++) {
      js_value_t *element;
      err = js_get_element(env, argv[1], i, &element);
      assert(err == 0);

      float value;
      if (!bare_win_ui__read_float(env, element, "dash", &value)) return nullptr;

      dashes.Append(value);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
