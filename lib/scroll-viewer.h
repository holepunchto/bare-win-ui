#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_scroll_viewer_event_view_changed = 1 << 0,
};

struct bare_win_ui_scroll_viewer_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  ScrollViewer::ViewChanged_revoker view_changed;
};

static void
bare_win_ui_scroll_viewer__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_scroll_viewer_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_scroll_viewer_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_scroll_viewer_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_scroll_viewer__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_scroll_viewer__on_view_changed(bare_win_ui_scroll_viewer_events_t *events, IInspectable const &sender) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  auto viewer = sender.as<ScrollViewer>();

  js_value_t *argv[2] = {
    bare_win_ui__from_double(env, viewer.HorizontalOffset()),
    bare_win_ui__from_double(env, viewer.VerticalOffset()),
  };

  bare_win_ui__emit(env, events->ctx, "_onviewchanged", 2, argv);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_scroll_viewer_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  bare_win_ui_scroll_viewer_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_scroll_viewer_event_view_changed) == 0) {
      events->view_changed.revoke();
    } else if (!events->view_changed) {
      events->view_changed = viewer.ViewChanged(auto_revoke, [events](IInspectable const &sender, ScrollViewerViewChangedEventArgs const &) {
        bare_win_ui_scroll_viewer__on_view_changed(events, sender);
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_scroll_viewer_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, ScrollViewer());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, viewer.Content().try_as<UIElement>());
    } else {
      UIElement content = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "content", &content)) return nullptr;

      viewer.Content(content);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// The offsets are read from the viewer and written through `ChangeView`, which
// is the only way it accepts one.
static js_value_t *
bare_win_ui_scroll_viewer_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_point(env, viewer.HorizontalOffset(), viewer.VerticalOffset());
    } else {
      double x, y;

      if (!bare_win_ui__read_double(env, argv[1], "x", &x)) return nullptr;
      if (!bare_win_ui__read_double(env, argv[2], "y", &y)) return nullptr;

      viewer.ChangeView(x, y, nullptr, true);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// What the viewer thinks it holds against what it can show, which is what
// decides whether there is anything to scroll at all.
static js_value_t *
bare_win_ui_scroll_viewer_extent(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  try {
#define V(name, value) \
  { \
    err = js_set_named_property(env, result, name, bare_win_ui__from_double(env, value)); \
    assert(err == 0); \
  }

    V("extentWidth", viewer.ExtentWidth())
    V("extentHeight", viewer.ExtentHeight())
    V("viewportWidth", viewer.ViewportWidth())
    V("viewportHeight", viewer.ViewportHeight())
    V("scrollableWidth", viewer.ScrollableWidth())
    V("scrollableHeight", viewer.ScrollableHeight())
#undef V
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_scroll_mode(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  bool horizontal, vertical;

  if (!bare_win_ui__read_bool(env, argv[1], "horizontal", &horizontal)) return nullptr;
  if (!bare_win_ui__read_bool(env, argv[2], "vertical", &vertical)) return nullptr;

  try {
    viewer.HorizontalScrollMode(horizontal ? ScrollMode::Auto : ScrollMode::Disabled);
    viewer.VerticalScrollMode(vertical ? ScrollMode::Auto : ScrollMode::Disabled);

    viewer.HorizontalScrollBarVisibility(horizontal ? ScrollBarVisibility::Auto : ScrollBarVisibility::Disabled);
    viewer.VerticalScrollBarVisibility(vertical ? ScrollBarVisibility::Auto : ScrollBarVisibility::Disabled);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}
