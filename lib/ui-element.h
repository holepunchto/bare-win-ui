#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_ui_element_opacity(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, element.Opacity());
    } else {
      double opacity;
      if (!bare_win_ui__read_double(env, argv[1], "opacity", &opacity)) return nullptr;

      element.Opacity(opacity);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static void
bare_win_ui_ui_element_opacity_typed(js_value_t *receiver, uint32_t bare_tag, double value, js_typed_callback_info_t *info) {
  auto element = bare_winrt__object(bare_tag).try_as<UIElement>();

  if (element == nullptr) return;

  try {
    element.Opacity(value);
  } catch (hresult_error const &) {
  }
}

enum {
  bare_win_ui_ui_element_event_pointer_pressed = 1 << 0,
  bare_win_ui_ui_element_event_pointer_released = 1 << 1,
  bare_win_ui_ui_element_event_pointer_moved = 1 << 2,
  bare_win_ui_ui_element_event_pointer_canceled = 1 << 3,
};

struct bare_win_ui_ui_element_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  UIElement::PointerPressed_revoker pointer_pressed;
  UIElement::PointerReleased_revoker pointer_released;
  UIElement::PointerMoved_revoker pointer_moved;
  UIElement::PointerCanceled_revoker pointer_canceled;
};

static void
bare_win_ui_ui_element__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_ui_element_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_ui_element_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_ui_element_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_ui_element__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static bool
bare_win_ui_ui_element__emit(bare_win_ui_ui_element_events_t *events, const char *name, IInspectable const &sender, PointerRoutedEventArgs const &args) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  bool handled = false;

  js_value_t *receiver;
  err = js_get_reference_value(env, events->ctx, &receiver);
  assert(err == 0);

  if (receiver != nullptr) {
    auto point = args.GetCurrentPoint(sender.as<UIElement>());
    auto position = point.Position();

    js_value_t *argv[4] = {
      bare_win_ui__from_double(env, position.X),
      bare_win_ui__from_double(env, position.Y),
      bare_win_ui__from_double(env, double(point.PointerId())),
      bare_win_ui__from_int32(env, int32_t(args.Pointer().PointerDeviceType())),
    };

    js_value_t *fn;
    err = js_get_named_property(env, receiver, name, &fn);
    assert(err == 0);

    js_value_t *result;
    err = js_call_function(env, receiver, fn, 4, argv, &result);

    if (err == 0) {
      bool value;

      if (js_get_value_bool(env, result, &value) == 0) handled = value;
    }
  }

  err = js_close_handle_scope(env, scope);
  assert(err == 0);

  return handled;
}

static js_value_t *
bare_win_ui_ui_element_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  bare_win_ui_ui_element_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_ui_element_event_pointer_pressed) == 0) {
      events->pointer_pressed.revoke();
    } else if (!events->pointer_pressed) {
      events->pointer_pressed = element.PointerPressed(auto_revoke, [events](IInspectable const &sender, PointerRoutedEventArgs const &args) {
        args.Handled(bare_win_ui_ui_element__emit(events, "_onpointerpressed", sender, args));
      });
    }

    if ((mask & bare_win_ui_ui_element_event_pointer_released) == 0) {
      events->pointer_released.revoke();
    } else if (!events->pointer_released) {
      events->pointer_released = element.PointerReleased(auto_revoke, [events](IInspectable const &sender, PointerRoutedEventArgs const &args) {
        args.Handled(bare_win_ui_ui_element__emit(events, "_onpointerreleased", sender, args));
      });
    }

    if ((mask & bare_win_ui_ui_element_event_pointer_moved) == 0) {
      events->pointer_moved.revoke();
    } else if (!events->pointer_moved) {
      events->pointer_moved = element.PointerMoved(auto_revoke, [events](IInspectable const &sender, PointerRoutedEventArgs const &args) {
        args.Handled(bare_win_ui_ui_element__emit(events, "_onpointermoved", sender, args));
      });
    }

    if ((mask & bare_win_ui_ui_element_event_pointer_canceled) == 0) {
      events->pointer_canceled.revoke();
    } else if (!events->pointer_canceled) {
      events->pointer_canceled = element.PointerCanceled(auto_revoke, [events](IInspectable const &sender, PointerRoutedEventArgs const &args) {
        args.Handled(bare_win_ui_ui_element__emit(events, "_onpointercanceled", sender, args));
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_ui_element_measure(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  double width, height;

  if (!bare_win_ui__read_double(env, argv[1], "width", &width)) return nullptr;
  if (!bare_win_ui__read_double(env, argv[2], "height", &height)) return nullptr;

  try {
    element.Measure(Size(static_cast<float>(width), static_cast<float>(height)));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_ui_element_desired_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    auto size = element.DesiredSize();

    result = bare_win_ui__from_fields(env, {{"width", size.Width}, {"height", size.Height}});
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_ui_element_is_hit_test_visible(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      err = js_get_boolean(env, element.IsHitTestVisible(), &result);
      assert(err == 0);
    } else {
      bool visible;
      if (!bare_win_ui__read_bool(env, argv[1], "visible", &visible)) return nullptr;

      element.IsHitTestVisible(visible);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
