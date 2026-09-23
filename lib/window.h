#pragma once

#include <assert.h>
#include <js.h>
#include <math.h>
#include <winuser.h>

#include "bridging.h"

enum {
  bare_win_ui_window_event_size_changed = 1 << 0,
};

struct bare_win_ui_window_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  Window::SizeChanged_revoker size_changed;
};

// `AppWindow` sizes in physical pixels, everything else in DIPs.
static inline double
bare_win_ui_window__get_scale(Window const &window) {
  auto dpi = GetDpiForWindow(GetWindowFromWindowId(window.AppWindow().Id()));

  return double(dpi) / 96;
}

static js_value_t *
bare_win_ui_window_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, Window());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_window_title(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_string(env, window.Title());
    } else {
      hstring title;
      if (!bare_win_ui__read_string(env, argv[1], "title", &title)) return nullptr;

      window.Title(title);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_window_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, window.Content());
    } else {
      UIElement content = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "content", &content)) return nullptr;

      window.Content(content);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_window_bounds(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_rect(env, window.Bounds());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_window_activate(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  try {
    window.Activate();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_window_close(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  try {
    window.Close();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_window__resize(js_env_t *env, js_callback_info_t *info, bool client) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  double width;
  if (!bare_win_ui__read_double(env, argv[1], "width", &width)) return nullptr;

  double height;
  if (!bare_win_ui__read_double(env, argv[2], "height", &height)) return nullptr;

  try {
    auto scale = bare_win_ui_window__get_scale(window);

    SizeInt32 size = {int32_t(lround(width * scale)), int32_t(lround(height * scale))};

    if (client) window.AppWindow().ResizeClient(size);
    else window.AppWindow().Resize(size);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_window_resize(js_env_t *env, js_callback_info_t *info) {
  return bare_win_ui_window__resize(env, info, false);
}

static js_value_t *
bare_win_ui_window_resize_client(js_env_t *env, js_callback_info_t *info) {
  return bare_win_ui_window__resize(env, info, true);
}

static void
bare_win_ui_window__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_window_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_window_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_window_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_window__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_window__on_size_changed(bare_win_ui_window_events_t *events, WindowSizeChangedEventArgs const &args) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  auto size = args.Size();

  js_value_t *argv[2] = {
    bare_win_ui__from_double(env, size.Width),
    bare_win_ui__from_double(env, size.Height),
  };

  bare_win_ui__emit(env, events->ctx, "_onsizechanged", 2, argv);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_window_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  Window window = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &window) < 0) return nullptr;

  bare_win_ui_window_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_window_event_size_changed) == 0) {
      events->size_changed.revoke();
    } else if (!events->size_changed) {
      events->size_changed = window.SizeChanged(auto_revoke, [events](auto const &, WindowSizeChangedEventArgs const &args) {
        bare_win_ui_window__on_size_changed(events, args);
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}
