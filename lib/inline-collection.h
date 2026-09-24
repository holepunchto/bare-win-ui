#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_inline_collection_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  InlineCollection collection = nullptr;
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
bare_win_ui_inline_collection_append(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  InlineCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  Inline item = nullptr;
  if (bare_winrt__read_type(env, argv[1], "inline", &item) < 0) return nullptr;

  try {
    collection.Append(item);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_inline_collection_clear(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  InlineCollection collection = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &collection) < 0) return nullptr;

  try {
    collection.Clear();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
