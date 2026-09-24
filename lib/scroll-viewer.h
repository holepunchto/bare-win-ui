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

// What the event itself carries is whether the view is still moving; where it
// moved to is read from the viewer, as it is anywhere else.
static void
bare_win_ui_scroll_viewer__on_view_changed(bare_win_ui_scroll_viewer_events_t *events, bool intermediate) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *argv[1];
  err = js_get_boolean(env, intermediate, &argv[0]);
  assert(err == 0);

  bare_win_ui__emit(env, events->ctx, "_onviewchanged", 1, argv);

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
      events->view_changed = viewer.ViewChanged(auto_revoke, [events](IInspectable const &, ScrollViewerViewChangedEventArgs const &args) {
        bare_win_ui_scroll_viewer__on_view_changed(events, args.IsIntermediate());
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

static js_value_t *
bare_win_ui_scroll_viewer_horizontal_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.HorizontalOffset());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_vertical_offset(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.VerticalOffset());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_extent_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.ExtentWidth());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_extent_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.ExtentHeight());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_viewport_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.ViewportWidth());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_viewport_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.ViewportHeight());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_scrollable_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.ScrollableWidth());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_scrollable_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_double(env, viewer.ScrollableHeight());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// The only way a `ScrollViewer` accepts an offset, and it takes each of the
// three as a reference so that a caller can leave one where it is.
static js_value_t *
bare_win_ui_scroll_viewer_change_view(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 5);

  ScrollViewer viewer = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &viewer) < 0) return nullptr;

  IReference<double> horizontal = nullptr;
  if (!bare_win_ui__read_optional<double>(env, argv[1], "horizontalOffset", &horizontal)) return nullptr;

  IReference<double> vertical = nullptr;
  if (!bare_win_ui__read_optional<double>(env, argv[2], "verticalOffset", &vertical)) return nullptr;

  IReference<float> zoom = nullptr;
  if (!bare_win_ui__read_optional<float>(env, argv[3], "zoomFactor", &zoom)) return nullptr;

  bool disable_animation;
  if (!bare_win_ui__read_bool(env, argv[4], "disableAnimation", &disable_animation)) return nullptr;

  js_value_t *result = nullptr;

  try {
    err = js_get_boolean(env, viewer.ChangeView(horizontal, vertical, zoom, disable_animation), &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_horizontal_scroll_mode(js_env_t *env, js_callback_info_t *info) {
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
      result = bare_win_ui__from_int32(env, int32_t(viewer.HorizontalScrollMode()));
    } else {
      int32_t value;
      if (!bare_win_ui__read_int32(env, argv[1], "horizontalScrollMode", &value)) return nullptr;

      viewer.HorizontalScrollMode(ScrollMode(value));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_vertical_scroll_mode(js_env_t *env, js_callback_info_t *info) {
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
      result = bare_win_ui__from_int32(env, int32_t(viewer.VerticalScrollMode()));
    } else {
      int32_t value;
      if (!bare_win_ui__read_int32(env, argv[1], "verticalScrollMode", &value)) return nullptr;

      viewer.VerticalScrollMode(ScrollMode(value));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_horizontal_scroll_bar_visibility(js_env_t *env, js_callback_info_t *info) {
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
      result = bare_win_ui__from_int32(env, int32_t(viewer.HorizontalScrollBarVisibility()));
    } else {
      int32_t value;
      if (!bare_win_ui__read_int32(env, argv[1], "horizontalScrollBarVisibility", &value)) return nullptr;

      viewer.HorizontalScrollBarVisibility(ScrollBarVisibility(value));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_scroll_viewer_vertical_scroll_bar_visibility(js_env_t *env, js_callback_info_t *info) {
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
      result = bare_win_ui__from_int32(env, int32_t(viewer.VerticalScrollBarVisibility()));
    } else {
      int32_t value;
      if (!bare_win_ui__read_int32(env, argv[1], "verticalScrollBarVisibility", &value)) return nullptr;

      viewer.VerticalScrollBarVisibility(ScrollBarVisibility(value));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
