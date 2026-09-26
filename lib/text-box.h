#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_text_box_event_text_changing = 1 << 0,
  bare_win_ui_text_box_event_text_changed = 1 << 1,
  bare_win_ui_text_box_event_selection_changed = 1 << 2,
  bare_win_ui_text_box_event_got_focus = 1 << 3,
  bare_win_ui_text_box_event_lost_focus = 1 << 4,
  bare_win_ui_text_box_event_key_down = 1 << 5,
  bare_win_ui_text_box_event_loaded = 1 << 6,
};

struct bare_win_ui_text_box_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  TextBox::TextChanging_revoker text_changing;
  TextBox::TextChanged_revoker text_changed;
  TextBox::SelectionChanged_revoker selection_changed;
  TextBox::GotFocus_revoker got_focus;
  TextBox::LostFocus_revoker lost_focus;
  TextBox::KeyDown_revoker key_down;
  TextBox::Loaded_revoker loaded;
};

static void
bare_win_ui_text_box__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_text_box_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_text_box_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_text_box_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_text_box__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_text_box__emit(bare_win_ui_text_box_events_t *events, const char *name, size_t argc, js_value_t *const *argv) {
  int err;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(events->env, &scope);
  assert(err == 0);

  bare_win_ui__emit(events->env, events->ctx, name, argc, argv);

  err = js_close_handle_scope(events->env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_text_box_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  TextBox box = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr;

  bare_win_ui_text_box_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_text_box_event_text_changing) == 0) {
      events->text_changing.revoke();
    } else if (!events->text_changing) {
      events->text_changing = box.TextChanging(auto_revoke, [events](TextBox const &, TextBoxTextChangingEventArgs const &) {
        bare_win_ui_text_box__emit(events, "_ontextchanging", 0, nullptr);
      });
    }

    if ((mask & bare_win_ui_text_box_event_text_changed) == 0) {
      events->text_changed.revoke();
    } else if (!events->text_changed) {
      events->text_changed = box.TextChanged(auto_revoke, [events](IInspectable const &, TextChangedEventArgs const &) {
        bare_win_ui_text_box__emit(events, "_ontextchanged", 0, nullptr);
      });
    }

    if ((mask & bare_win_ui_text_box_event_selection_changed) == 0) {
      events->selection_changed.revoke();
    } else if (!events->selection_changed) {
      events->selection_changed = box.SelectionChanged(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_text_box__emit(events, "_onselectionchanged", 0, nullptr);
      });
    }

    if ((mask & bare_win_ui_text_box_event_got_focus) == 0) {
      events->got_focus.revoke();
    } else if (!events->got_focus) {
      events->got_focus = box.GotFocus(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_text_box__emit(events, "_ongotfocus", 0, nullptr);
      });
    }

    if ((mask & bare_win_ui_text_box_event_lost_focus) == 0) {
      events->lost_focus.revoke();
    } else if (!events->lost_focus) {
      events->lost_focus = box.LostFocus(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_text_box__emit(events, "_onlostfocus", 0, nullptr);
      });
    }

    if ((mask & bare_win_ui_text_box_event_loaded) == 0) {
      events->loaded.revoke();
    } else if (!events->loaded) {
      events->loaded = box.Loaded(auto_revoke, [events](IInspectable const &, RoutedEventArgs const &) {
        bare_win_ui_text_box__emit(events, "_onloaded", 0, nullptr);
      });
    }

    if ((mask & bare_win_ui_text_box_event_key_down) == 0) {
      events->key_down.revoke();
    } else if (!events->key_down) {
      events->key_down = box.KeyDown(auto_revoke, [events](IInspectable const &, KeyRoutedEventArgs const &args) {
        int err;

        js_handle_scope_t *scope;
        err = js_open_handle_scope(events->env, &scope);
        assert(err == 0);

        js_value_t *key;
        err = js_create_int32(events->env, static_cast<int32_t>(args.Key()), &key);
        assert(err == 0);

        bare_win_ui__emit(events->env, events->ctx, "_onkeydown", 1, &key);

        err = js_close_handle_scope(events->env, scope);
        assert(err == 0);
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_text_box_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, TextBox());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

#define BARE_WIN_UI_TEXT_BOX_STRING(name, getter, setter) \
  static js_value_t * \
  bare_win_ui_text_box_##name(js_env_t *env, js_callback_info_t *info) { \
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
    TextBox box = nullptr; \
    if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr; \
\
    js_value_t *result = nullptr; \
\
    try { \
      if (argc == 1) { \
        result = bare_win_ui__from_string(env, box.getter()); \
      } else { \
        hstring value; \
        if (!bare_win_ui__read_string(env, argv[1], #name, &value)) return nullptr; \
\
        box.setter(value); \
      } \
    } catch (hresult_error const &error) { \
      bare_win_ui__throw(env, error); \
\
      return nullptr; \
    } \
\
    return result; \
  }

#define BARE_WIN_UI_TEXT_BOX_SCALAR(name, getter, setter, type, from, read, cast) \
  static js_value_t * \
  bare_win_ui_text_box_##name(js_env_t *env, js_callback_info_t *info) { \
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
    TextBox box = nullptr; \
    if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr; \
\
    js_value_t *result = nullptr; \
\
    try { \
      if (argc == 1) { \
        result = from(env, (type) box.getter()); \
      } else { \
        type value; \
        if (!read(env, argv[1], #name, &value)) return nullptr; \
\
        box.setter(cast value); \
      } \
    } catch (hresult_error const &error) { \
      bare_win_ui__throw(env, error); \
\
      return nullptr; \
    } \
\
    return result; \
  }

BARE_WIN_UI_TEXT_BOX_STRING(text, Text, Text)
BARE_WIN_UI_TEXT_BOX_STRING(placeholder_text, PlaceholderText, PlaceholderText)

BARE_WIN_UI_TEXT_BOX_SCALAR(is_read_only, IsReadOnly, IsReadOnly, bool, bare_win_ui__from_boolean, bare_win_ui__read_bool, )
BARE_WIN_UI_TEXT_BOX_SCALAR(accepts_return, AcceptsReturn, AcceptsReturn, bool, bare_win_ui__from_boolean, bare_win_ui__read_bool, )
BARE_WIN_UI_TEXT_BOX_SCALAR(is_spell_check_enabled, IsSpellCheckEnabled, IsSpellCheckEnabled, bool, bare_win_ui__from_boolean, bare_win_ui__read_bool, )
BARE_WIN_UI_TEXT_BOX_SCALAR(selection_start, SelectionStart, SelectionStart, int32_t, bare_win_ui__from_int32, bare_win_ui__read_int32, )
BARE_WIN_UI_TEXT_BOX_SCALAR(selection_length, SelectionLength, SelectionLength, int32_t, bare_win_ui__from_int32, bare_win_ui__read_int32, )
BARE_WIN_UI_TEXT_BOX_SCALAR(text_wrapping, TextWrapping, TextWrapping, int32_t, bare_win_ui__from_int32, bare_win_ui__read_int32, (TextWrapping))
#undef BARE_WIN_UI_TEXT_BOX_STRING
#undef BARE_WIN_UI_TEXT_BOX_SCALAR

// An input scope is an object holding a list of names, and what a caller has
// is one name, so the object is made here rather than left for them to build.
static js_value_t *
bare_win_ui_text_box_input_scope(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  TextBox box = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &box) < 0) return nullptr;

  int32_t name;
  if (!bare_win_ui__read_int32(env, argv[1], "name", &name)) return nullptr;

  try {
    InputScope scope;
    InputScopeName value;

    value.NameValue(static_cast<InputScopeNameValue>(name));

    scope.Names().Append(value);

    box.InputScope(scope);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_text_box_text_alignment(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBox text_box = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_box) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_int32(env, int32_t(text_box.TextAlignment()));
    } else {
      int32_t text_alignment;
      if (!bare_win_ui__read_int32(env, argv[1], "text_alignment", &text_alignment)) return nullptr;

      text_box.TextAlignment(TextAlignment(text_alignment));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
