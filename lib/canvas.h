#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_canvas_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, Canvas());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_canvas_get_left(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_double(env, Canvas::GetLeft(element));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_canvas_set_left(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  double length;
  if (!bare_win_ui__read_double(env, argv[1], "length", &length)) return nullptr;

  try {
    Canvas::SetLeft(element, length);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static void
bare_win_ui_canvas_set_left_typed(js_value_t *receiver, uint32_t bare_tag, double length, js_typed_callback_info_t *info) {
  auto element = bare_winrt__object(bare_tag).try_as<UIElement>();

  if (element == nullptr) return;

  try {
    Canvas::SetLeft(element, length);
  } catch (hresult_error const &) {
  }
}

static js_value_t *
bare_win_ui_canvas_get_top(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_double(env, Canvas::GetTop(element));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_canvas_set_top(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  double length;
  if (!bare_win_ui__read_double(env, argv[1], "length", &length)) return nullptr;

  try {
    Canvas::SetTop(element, length);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static void
bare_win_ui_canvas_set_top_typed(js_value_t *receiver, uint32_t bare_tag, double length, js_typed_callback_info_t *info) {
  auto element = bare_winrt__object(bare_tag).try_as<UIElement>();

  if (element == nullptr) return;

  try {
    Canvas::SetTop(element, length);
  } catch (hresult_error const &) {
  }
}

static js_value_t *
bare_win_ui_canvas_set_z_index(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  int32_t index;
  if (!bare_win_ui__read_int32(env, argv[1], "index", &index)) return nullptr;

  try {
    Canvas::SetZIndex(element, index);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}
