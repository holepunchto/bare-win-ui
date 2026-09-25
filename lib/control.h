#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

// Focus is given to a control and never taken away, so letting go is moving it
// on rather than clearing it, which is what `FocusManager` is for.
static js_value_t *
bare_win_ui_control_focus(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  int32_t state;
  if (!bare_win_ui__read_int32(env, argv[1], "state", &state)) return nullptr;

  js_value_t *result;

  try {
    err = js_get_boolean(env, control.Focus(static_cast<FocusState>(state)), &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// A desktop app has no one focus scope to move within, so the search has to be
// told which tree it is moving within, and the tree an element is in is the
// content of the root it is loaded into.
static js_value_t *
bare_win_ui_focus_manager_try_move_focus(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  UIElement element = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &element) < 0) return nullptr;

  int32_t direction;
  if (!bare_win_ui__read_int32(env, argv[1], "direction", &direction)) return nullptr;

  js_value_t *result;

  try {
    FindNextElementOptions options;
    options.SearchRoot(element.XamlRoot().Content());

    auto moved = FocusManager::TryMoveFocus(static_cast<FocusNavigationDirection>(direction), options);

    err = js_get_boolean(env, moved, &result);
    assert(err == 0);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

#define BARE_WIN_UI_CONTROL(name, property, type, from, read, set) \
  static js_value_t * \
  bare_win_ui_control_##name(js_env_t *env, js_callback_info_t *info) { \
    int err; \
\
    size_t argc = 2; \
    js_value_t *argv[2]; \
\
    err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr); \
    assert(err == 0); \
\
    assert(argc == 1 || argc == 2); \
\
    Control control = nullptr; \
    if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr; \
\
    js_value_t *result = nullptr; \
\
    try { \
      if (argc == 1) { \
        result = from(env, control.property()); \
      } else { \
        set \
      } \
    } catch (hresult_error const &error) { \
      bare_win_ui__throw(env, error); \
\
      return nullptr; \
    } \
\
    return result; \
  }

BARE_WIN_UI_CONTROL(
  is_enabled, IsEnabled, bool, bare_win_ui__from_boolean, bare_win_ui__read_bool,
  bool value;
  if (!bare_win_ui__read_bool(env, argv[1], "isEnabled", &value)) return nullptr;

  control.IsEnabled(value);
)

// A background is a `Panel` property on a canvas and a `Control` property on a
// text box, and the two are different classes, so both are bound.
BARE_WIN_UI_CONTROL(
  background, Background, Brush, bare_win_ui__from_object, bare_win_ui__read_nullable,
  Brush brush = nullptr;
  if (!bare_win_ui__read_nullable(env, argv[1], "background", &brush)) return nullptr;

  control.Background(brush);
)
#undef BARE_WIN_UI_CONTROL

// A `Control` has a background, a border and a corner radius of its own, where
// a `Canvas` has none of them and needs composition visuals instead. Using the
// control's own is not only simpler: a composition child visual put on a
// templated control fights the template it already has.
static js_value_t *
bare_win_ui_control_border_brush(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, control.BorderBrush());
    } else {
      Brush brush = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "borderBrush", &brush)) return nullptr;

      control.BorderBrush(brush);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// The rectangle WinUI draws over a control that has the focus, which is the
// system's own and not the template's, and so is the one a caller can turn
// off.
static js_value_t *
bare_win_ui_control_use_system_focus_visuals(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_boolean(env, control.UseSystemFocusVisuals());
    } else {
      bool value;
      if (!bare_win_ui__read_bool(env, argv[1], "useSystemFocusVisuals", &value)) return nullptr;

      control.UseSystemFocusVisuals(value);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// What a control draws with, as against what it draws on.
static js_value_t *
bare_win_ui_control_foreground(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, control.Foreground());
    } else {
      Brush brush = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "foreground", &brush)) return nullptr;

      control.Foreground(brush);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// Both are value types with four parts, and every part is the same here, so
// one number crosses rather than four.
static js_value_t *
bare_win_ui_control_border_thickness(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  double thickness;
  if (!bare_win_ui__read_double(env, argv[1], "thickness", &thickness)) return nullptr;

  try {
    control.BorderThickness(ThicknessHelper::FromUniformLength(thickness));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

// A template's parts are named, and the protected accessor for one is a public
// interface at the ABI, which is the only way in from outside the control.
static js_value_t *
bare_win_ui_control_template_child(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  hstring name;
  if (!bare_win_ui__read_string(env, argv[1], "name", &name)) return nullptr;

  js_value_t *result;

  try {
    auto protect = control.as<IControlProtected>();

    result = bare_win_ui__from_object(env, protect.GetTemplateChild(name));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// A control's template pads its content, and a node measured by the layout has
// only the room the layout gave it.
static js_value_t *
bare_win_ui_control_padding(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  double padding;
  if (!bare_win_ui__read_double(env, argv[1], "padding", &padding)) return nullptr;

  try {
    control.Padding(ThicknessHelper::FromUniformLength(padding));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_control_corner_radius(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  Control control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  double radius;
  if (!bare_win_ui__read_double(env, argv[1], "radius", &radius)) return nullptr;

  try {
    control.CornerRadius(CornerRadiusHelper::FromUniformRadius(radius));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
