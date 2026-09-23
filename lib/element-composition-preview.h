#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_element_composition_preview_get_element_visual(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_object(env, ElementCompositionPreview::GetElementVisual(element));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_element_composition_preview_get_element_child_visual(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_object(env, ElementCompositionPreview::GetElementChildVisual(element));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_element_composition_preview_set_element_child_visual(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "element", &element) < 0) return nullptr;

  Visual visual = nullptr;
  if (!bare_win_ui__read_nullable(env, argv[1], "visual", &visual)) return nullptr;

  js_value_t *result = nullptr;

  try {
    ElementCompositionPreview::SetElementChildVisual(element, visual);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
