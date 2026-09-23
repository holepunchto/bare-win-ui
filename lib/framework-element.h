#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_framework_element_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  FrameworkElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, element.Width());
    } else {
      double width;
      if (!bare_win_ui__read_double(env, argv[1], "width", &width)) return nullptr;

      element.Width(width);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static void
bare_win_ui_framework_element_width_typed(js_value_t *receiver, uint32_t bare_tag, double value, js_typed_callback_info_t *info) {
  auto element = bare_winrt__object(bare_tag).try_as<FrameworkElement>();

  if (element == nullptr) return;

  try {
    element.Width(value);
  } catch (hresult_error const &) {
  }
}

static js_value_t *
bare_win_ui_framework_element_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  FrameworkElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, element.Height());
    } else {
      double height;
      if (!bare_win_ui__read_double(env, argv[1], "height", &height)) return nullptr;

      element.Height(height);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static void
bare_win_ui_framework_element_height_typed(js_value_t *receiver, uint32_t bare_tag, double value, js_typed_callback_info_t *info) {
  auto element = bare_winrt__object(bare_tag).try_as<FrameworkElement>();

  if (element == nullptr) return;

  try {
    element.Height(value);
  } catch (hresult_error const &) {
  }
}

static js_value_t *
bare_win_ui_framework_element_actual_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  FrameworkElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, element.ActualWidth());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_framework_element_actual_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  FrameworkElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, element.ActualHeight());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_framework_element_parent(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  FrameworkElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_object(env, element.Parent());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
