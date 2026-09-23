#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_ui_element_collection_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, collection.Size());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_collection_get_at(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    uint32_t index;
    if (!bare_win_ui__read_uint32(env, argv[1], "index", &index)) return nullptr;

    result = bare_win_ui__from_object(env, collection.GetAt(index));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_collection_index_of(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    UIElement value = nullptr;
    if (bare_winrt__read_type(env, argv[1], "value", &value) < 0) return nullptr;

    uint32_t index;

    result = bare_win_ui__from_int32(env, collection.IndexOf(value, index) ? int32_t(index) : -1);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_collection_append(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    UIElement value = nullptr;
    if (bare_winrt__read_type(env, argv[1], "value", &value) < 0) return nullptr;

    collection.Append(value);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_collection_insert_at(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    uint32_t index;
    if (!bare_win_ui__read_uint32(env, argv[1], "index", &index)) return nullptr;

    UIElement value = nullptr;
    if (bare_winrt__read_type(env, argv[2], "value", &value) < 0) return nullptr;

    collection.InsertAt(index, value);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_collection_remove_at(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    uint32_t index;
    if (!bare_win_ui__read_uint32(env, argv[1], "index", &index)) return nullptr;

    collection.RemoveAt(index);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_collection_clear(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElementCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    collection.Clear();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
