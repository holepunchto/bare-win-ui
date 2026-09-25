#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_password_box_event_password_changed = 1 << 0,
  bare_win_ui_password_box_event_got_focus = 1 << 1,
  bare_win_ui_password_box_event_lost_focus = 1 << 2,
  bare_win_ui_password_box_event_loaded = 1 << 3,
};

struct bare_win_ui_password_box_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  PasswordBox::PasswordChanged_revoker password_changed;
  PasswordBox::GotFocus_revoker got_focus;
  PasswordBox::LostFocus_revoker lost_focus;
  PasswordBox::Loaded_revoker loaded;
};

static void
bare_win_ui_password_box__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_password_box_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_password_box_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_password_box_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_password_box__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_password_box__emit(bare_win_ui_password_box_events_t *events, const char *name) {
  int err;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(events->env, &scope);
  assert(err == 0);

  bare_win_ui__emit(events->env, events->ctx, name, 0, nullptr);

  err = js_close_handle_scope(events->env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_password_box_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  PasswordBox box = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr;

  bare_win_ui_password_box_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_password_box_event_password_changed) == 0) {
      events->password_changed.revoke();
    } else if (!events->password_changed) {
      events->password_changed = box.PasswordChanged(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_password_box__emit(events, "_onpasswordchanged");
      });
    }

    if ((mask & bare_win_ui_password_box_event_got_focus) == 0) {
      events->got_focus.revoke();
    } else if (!events->got_focus) {
      events->got_focus = box.GotFocus(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_password_box__emit(events, "_ongotfocus");
      });
    }

    if ((mask & bare_win_ui_password_box_event_loaded) == 0) {
      events->loaded.revoke();
    } else if (!events->loaded) {
      events->loaded = box.Loaded(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_password_box__emit(events, "_onloaded");
      });
    }

    if ((mask & bare_win_ui_password_box_event_lost_focus) == 0) {
      events->lost_focus.revoke();
    } else if (!events->lost_focus) {
      events->lost_focus = box.LostFocus(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_password_box__emit(events, "_onlostfocus");
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_password_box_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, PasswordBox());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

#define BARE_WIN_UI_PASSWORD_BOX_STRING(name, property) \
  static js_value_t * \
  bare_win_ui_password_box_##name(js_env_t *env, js_callback_info_t *info) { \
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
    PasswordBox box = nullptr; \
    if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr; \
\
    js_value_t *result = nullptr; \
\
    try { \
      if (argc == 1) { \
        result = bare_win_ui__from_string(env, box.property()); \
      } else { \
        hstring value; \
        if (!bare_win_ui__read_string(env, argv[1], #name, &value)) return nullptr; \
\
        box.property(value); \
      } \
    } catch (hresult_error const &error) { \
      bare_win_ui__throw(env, error); \
\
      return nullptr; \
    } \
\
    return result; \
  }

// Whether a box offers to show what it holds, which is a property of its own
// rather than a part of its template.
static js_value_t *
bare_win_ui_password_box_password_reveal_mode(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  PasswordBox box = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr;

  int32_t mode;
  if (!bare_win_ui__read_int32(env, argv[1], "mode", &mode)) return nullptr;

  try {
    box.PasswordRevealMode(static_cast<PasswordRevealMode>(mode));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

BARE_WIN_UI_PASSWORD_BOX_STRING(password, Password)
BARE_WIN_UI_PASSWORD_BOX_STRING(placeholder_text, PlaceholderText)
#undef BARE_WIN_UI_PASSWORD_BOX_STRING
