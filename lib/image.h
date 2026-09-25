#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_image_event_image_opened = 1 << 0,
  bare_win_ui_image_event_image_failed = 1 << 1,
};

struct bare_win_ui_image_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  Image::ImageOpened_revoker image_opened;
  Image::ImageFailed_revoker image_failed;
};

static void
bare_win_ui_image__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_image_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_image_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_image_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_image__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

// `ImageOpened` carries nothing at all and `ImageFailed` carries why, which is
// the only thing either of them says that the element cannot be asked for.
static void
bare_win_ui_image__on_image_opened(bare_win_ui_image_events_t *events) {
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
bare_win_ui_image__on_image_failed(bare_win_ui_image_events_t *events, hstring const &message) {
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
bare_win_ui_image_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  Image image = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &image) < 0) return nullptr;

  bare_win_ui_image_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_image_event_image_opened) == 0) {
      events->image_opened.revoke();
    } else if (!events->image_opened) {
      events->image_opened = image.ImageOpened(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_image__on_image_opened(events);
      });
    }

    if ((mask & bare_win_ui_image_event_image_failed) == 0) {
      events->image_failed.revoke();
    } else if (!events->image_failed) {
      events->image_failed = image.ImageFailed(auto_revoke, [events](IInspectable const &, ExceptionRoutedEventArgs const &args) {
        bare_win_ui_image__on_image_failed(events, args.ErrorMessage());
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_image_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, Image());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_image_source(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Image image = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &image) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, image.Source());
    } else {
      ImageSource source = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "source", &source)) return nullptr;

      image.Source(source);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_image_stretch(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Image image = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &image) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      err = js_create_int32(env, static_cast<int32_t>(image.Stretch()), &result);
      assert(err == 0);
    } else {
      int32_t stretch;
      if (!bare_win_ui__read_int32(env, argv[1], "stretch", &stretch)) return nullptr;

      image.Stretch(static_cast<Stretch>(stretch));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
