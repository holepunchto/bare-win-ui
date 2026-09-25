#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_bitmap_image_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, BitmapImage());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// The property takes a `Uri` and a caller has a string, which is the same
// translation `WebView2.Source` already makes.
static js_value_t *
bare_win_ui_bitmap_image_uri_source(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  BitmapImage image = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &image) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      auto uri = image.UriSource();

      if (uri == nullptr) {
        err = js_get_null(env, &result);
        assert(err == 0);
      } else {
        result = bare_win_ui__from_string(env, uri.AbsoluteUri());
      }
    } else {
      hstring uri;
      if (!bare_win_ui__read_string(env, argv[1], "uri", &uri)) return nullptr;

      image.UriSource(Uri(uri));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_bitmap_source_pixel_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  BitmapSource source = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &source) < 0) return nullptr;

  js_value_t *result;

  try {
    err = js_create_int32(env, source.PixelWidth(), &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_bitmap_source_pixel_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  BitmapSource source = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &source) < 0) return nullptr;

  js_value_t *result;

  try {
    err = js_create_int32(env, source.PixelHeight(), &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
