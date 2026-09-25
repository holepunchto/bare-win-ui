#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_toggle_switch_event_toggled = 1 << 0,
  bare_win_ui_toggle_switch_event_loaded = 1 << 1,
};

struct bare_win_ui_toggle_switch_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  ToggleSwitch::Toggled_revoker toggled;
  ToggleSwitch::Loaded_revoker loaded;
};

static void
bare_win_ui_toggle_switch__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_toggle_switch_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_toggle_switch_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_toggle_switch_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_toggle_switch__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_toggle_switch__emit(bare_win_ui_toggle_switch_events_t *events, const char *name) {
  int err;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(events->env, &scope);
  assert(err == 0);

  bare_win_ui__emit(events->env, events->ctx, name, 0, nullptr);

  err = js_close_handle_scope(events->env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_toggle_switch_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  ToggleSwitch control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  bare_win_ui_toggle_switch_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    // Raised whoever moved it, which is what a controlled switch has to be
    // fenced against above.
    if ((mask & bare_win_ui_toggle_switch_event_toggled) == 0) {
      events->toggled.revoke();
    } else if (!events->toggled) {
      events->toggled = control.Toggled(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_toggle_switch__emit(events, "_ontoggled");
      });
    }

    if ((mask & bare_win_ui_toggle_switch_event_loaded) == 0) {
      events->loaded.revoke();
    } else if (!events->loaded) {
      events->loaded = control.Loaded(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_toggle_switch__emit(events, "_onloaded");
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_toggle_switch_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, ToggleSwitch());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_toggle_switch_is_on(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  ToggleSwitch control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_boolean(env, control.IsOn());
    } else {
      bool value;
      if (!bare_win_ui__read_bool(env, argv[1], "isOn", &value)) return nullptr;

      control.IsOn(value);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// A toggle switch writes "On" and "Off" beside itself, which none of the other
// four offer and which a caller has no way to ask for here.
static js_value_t *
bare_win_ui_toggle_switch_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  ToggleSwitch control = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &control) < 0) return nullptr;

  hstring on;
  if (!bare_win_ui__read_string(env, argv[1], "on", &on)) return nullptr;

  hstring off;
  if (!bare_win_ui__read_string(env, argv[2], "off", &off)) return nullptr;

  try {
    control.OnContent(box_value(on));
    control.OffContent(box_value(off));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
