#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_canvas_path_builder_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, CanvasPathBuilder(CanvasDevice::GetSharedDevice()));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_canvas_path_builder_begin_figure(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  CanvasPathBuilder builder = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &builder) < 0) return nullptr;

  float x;
  if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

  float y;
  if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

  try {
    builder.BeginFigure(x, y);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_canvas_path_builder_add_line(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  CanvasPathBuilder builder = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &builder) < 0) return nullptr;

  float x;
  if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

  float y;
  if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

  try {
    builder.AddLine(x, y);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_canvas_path_builder_add_cubic_bezier(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 7;
  js_value_t *argv[7];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 7);

  CanvasPathBuilder builder = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &builder) < 0) return nullptr;

  float values[6];

  for (int i = 0; i < 6; i++) {
    if (!bare_win_ui__read_float(env, argv[i + 1], "value", &values[i])) return nullptr;
  }

  try {
    builder.AddCubicBezier({values[0], values[1]}, {values[2], values[3]}, {values[4], values[5]});
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_canvas_path_builder_add_arc(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 6;
  js_value_t *argv[6];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 6);

  CanvasPathBuilder builder = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &builder) < 0) return nullptr;

  float x;
  if (!bare_win_ui__read_float(env, argv[1], "x", &x)) return nullptr;

  float y;
  if (!bare_win_ui__read_float(env, argv[2], "y", &y)) return nullptr;

  float radius_x;
  if (!bare_win_ui__read_float(env, argv[3], "radius_x", &radius_x)) return nullptr;

  float radius_y;
  if (!bare_win_ui__read_float(env, argv[4], "radius_y", &radius_y)) return nullptr;

  float rotation;
  if (!bare_win_ui__read_float(env, argv[5], "rotation", &rotation)) return nullptr;

  try {
    builder.AddArc({x, y}, radius_x, radius_y, rotation, CanvasSweepDirection::Clockwise, CanvasArcSize::Small);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_canvas_path_builder_end_figure(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  CanvasPathBuilder builder = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &builder) < 0) return nullptr;

  bool closed;
  if (!bare_win_ui__read_bool(env, argv[1], "closed", &closed)) return nullptr;

  try {
    builder.EndFigure(closed ? CanvasFigureLoop::Closed : CanvasFigureLoop::Open);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
