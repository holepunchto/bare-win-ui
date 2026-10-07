#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_bitmap_image_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, BitmapImage());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

enum {
  bare_win_ui_bitmap_image_event_image_opened = 1 << 0,
  bare_win_ui_bitmap_image_event_image_failed = 1 << 1,
};

struct bare_win_ui_bitmap_image_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  BitmapImage::ImageOpened_revoker image_opened;
  BitmapImage::ImageFailed_revoker image_failed;
};

static void
bare_win_ui_bitmap_image__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_bitmap_image_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_bitmap_image_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_bitmap_image_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_bitmap_image__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_bitmap_image__on_image_opened(bare_win_ui_bitmap_image_events_t *events) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  bare_win_ui__emit(env, events->ctx, "_onimageopened", 0, nullptr);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static void
bare_win_ui_bitmap_image__on_image_failed(bare_win_ui_bitmap_image_events_t *events, hstring const &message) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *argv[1] = {bare_win_ui__from_string(env, message)};

  bare_win_ui__emit(env, events->ctx, "_onimagefailed", 1, argv);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_bitmap_image_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  BitmapImage image = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &image) < 0) return nullptr;

  bare_win_ui_bitmap_image_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_bitmap_image_event_image_opened) == 0) {
      events->image_opened.revoke();
    } else if (!events->image_opened) {
      events->image_opened = image.ImageOpened(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_bitmap_image__on_image_opened(events);
      });
    }

    if ((mask & bare_win_ui_bitmap_image_event_image_failed) == 0) {
      events->image_failed.revoke();
    } else if (!events->image_failed) {
      events->image_failed = image.ImageFailed(auto_revoke, [events](IInspectable const &, ExceptionRoutedEventArgs const &args) {
        bare_win_ui_bitmap_image__on_image_failed(events, args.ErrorMessage());
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

// The property takes a `Uri`, so the string from the caller is turned into one
// here.
static js_value_t *
bare_win_ui_bitmap_image_uri_source(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  BitmapImage image = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &image) < 0) return nullptr;

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

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  BitmapSource source = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &source) < 0) return nullptr;

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

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  BitmapSource source = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &source) < 0) return nullptr;

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
