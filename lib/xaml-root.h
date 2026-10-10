#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_xaml_root_event_changed = 1 << 0,
};

struct bare_win_ui_xaml_root_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  XamlRoot::Changed_revoker changed;
};

static void
bare_win_ui_xaml_root__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_xaml_root_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_xaml_root_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_xaml_root_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_xaml_root__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_xaml_root__on_changed(bare_win_ui_xaml_root_events_t *events) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  bare_win_ui__emit(env, events->ctx, "_onchanged", 0, nullptr);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_xaml_root_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  bare_win_ui_xaml_root_events_t *events;
  err = js_get_value_external(env, argv[1], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[2], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_xaml_root_event_changed) == 0) {
      events->changed.revoke();
    } else if (!events->changed) {
      events->changed = root.Changed(auto_revoke, [events](XamlRoot const &, XamlRootChangedEventArgs const &) {
        bare_win_ui_xaml_root__on_changed(events);
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_xaml_root_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  js_value_t *result;

  try {
    auto size = root.Size();

    result = bare_win_ui__from_fields(env, {{"width", size.Width}, {"height", size.Height}});
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_xaml_root_rasterization_scale(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_double(env, root.RasterizationScale());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_xaml_root_is_host_visible(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  XamlRoot root = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &root) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_boolean(env, root.IsHostVisible());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
