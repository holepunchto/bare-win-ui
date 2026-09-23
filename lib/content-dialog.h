#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"
#include "headless.h"

// A dialog answers through an `IAsyncOperation`, so the caller passes a
// callback and the answer is sent back to the thread the engine runs on.
enum {
  bare_win_ui_content_dialog_button_none = int(ContentDialogButton::None),
  bare_win_ui_content_dialog_button_primary = int(ContentDialogButton::Primary),
  bare_win_ui_content_dialog_button_secondary = int(ContentDialogButton::Secondary),
  bare_win_ui_content_dialog_button_close = int(ContentDialogButton::Close),

  bare_win_ui_content_dialog_result_none = int(ContentDialogResult::None),
  bare_win_ui_content_dialog_result_primary = int(ContentDialogResult::Primary),
  bare_win_ui_content_dialog_result_secondary = int(ContentDialogResult::Secondary),
};

struct bare_win_ui_content_dialog_show_t {
  bare_win_ui_state_t *state;
  js_env_t *env;
  js_ref_t *callback;
};

static void
bare_win_ui_content_dialog__on_show(bare_win_ui_content_dialog_show_t *show, int32_t result) {
  int err;

  auto env = show->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *callback;
  err = js_get_reference_value(env, show->callback, &callback);
  assert(err == 0);

  js_value_t *argv[1];
  err = js_create_int32(env, result, &argv[0]);
  assert(err == 0);

  js_value_t *receiver;
  err = js_get_null(env, &receiver);
  assert(err == 0);

  err = js_call_function(env, receiver, callback, 1, argv, nullptr);
  (void) err;

  err = js_delete_reference(env, show->callback);
  assert(err == 0);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);

  delete show;

  bare_win_ui__headless_release(show->state);
}

static js_value_t *
bare_win_ui_content_dialog_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, ContentDialog());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

#define V(name, property) \
  static js_value_t * \
  name(js_env_t *env, js_callback_info_t *info) { \
    int err; \
\
    size_t argc = 2; \
    js_value_t *argv[2]; \
\
    bare_win_ui_state_t *state; \
    err = js_get_callback_info(env, info, &argc, argv, nullptr, (void **) &state); \
    assert(err == 0); \
\
    assert(argc == 1 || argc == 2); \
\
    ContentDialog dialog = nullptr; \
    if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &dialog) < 0) return nullptr; \
\
    js_value_t *result = nullptr; \
\
    try { \
      if (argc == 1) { \
        result = bare_win_ui__from_string(env, dialog.property()); \
      } else { \
        hstring text; \
        if (!bare_win_ui__read_string(env, argv[1], "text", &text)) return nullptr; \
\
        dialog.property(text); \
      } \
    } catch (hresult_error const &error) { \
      bare_win_ui__throw(env, error); \
\
      return nullptr; \
    } \
\
    return result; \
  }

V(bare_win_ui_content_dialog_primary_button_text, PrimaryButtonText)
V(bare_win_ui_content_dialog_secondary_button_text, SecondaryButtonText)
V(bare_win_ui_content_dialog_close_button_text, CloseButtonText)
#undef V

// The title and the content take any object, and this layer gives them strings.
static js_value_t *
bare_win_ui_content_dialog_title(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  ContentDialog dialog = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &dialog) < 0) return nullptr;

  hstring text;
  if (!bare_win_ui__read_string(env, argv[1], "text", &text)) return nullptr;

  try {
    dialog.Title(box_value(text));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_content_dialog_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  ContentDialog dialog = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &dialog) < 0) return nullptr;

  hstring text;
  if (!bare_win_ui__read_string(env, argv[1], "text", &text)) return nullptr;

  try {
    dialog.Content(box_value(text));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_content_dialog_xaml_root(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  ContentDialog dialog = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &dialog) < 0) return nullptr;

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[1], "root", &root) < 0) return nullptr;

  try {
    dialog.XamlRoot(root);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_content_dialog_default_button(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  ContentDialog dialog = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &dialog) < 0) return nullptr;

  int32_t button;
  if (!bare_win_ui__read_int32(env, argv[1], "button", &button)) return nullptr;

  try {
    dialog.DefaultButton(ContentDialogButton(button));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_content_dialog_show_async(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  ContentDialog dialog = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &dialog) < 0) return nullptr;

  auto show = new bare_win_ui_content_dialog_show_t();

  show->state = state;

  show->env = env;

  err = js_create_reference(env, argv[1], 1, &show->callback);
  assert(err == 0);

  bare_win_ui__headless_hold(state);

  try {
    auto dispatcher = DispatcherQueue::GetForCurrentThread();

    dialog.ShowAsync().Completed([=](auto const &operation, AsyncStatus const status) {
      auto result = status == AsyncStatus::Completed ? int32_t(operation.GetResults()) : 0;

      dispatcher.TryEnqueue([=] {
        bare_win_ui_content_dialog__on_show(show, result);
      });
    });
  } catch (hresult_error const &error) {
    bare_win_ui__headless_release(show->state);

    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}
