#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_composition_target_event_rendering = 1 << 0,
};

struct bare_win_ui_composition_target_events_t {
  js_env_t *env;
  js_ref_t *ctx;

  CompositionTarget::Rendering_revoker rendering;
};

static void
bare_win_ui_composition_target__on_events_finalize(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto events = reinterpret_cast<bare_win_ui_composition_target_events_t *>(data);

  err = js_delete_reference(env, events->ctx);
  assert(err == 0);

  delete events;
}

static js_value_t *
bare_win_ui_composition_target_events(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto events = new bare_win_ui_composition_target_events_t();

  events->env = env;

  err = js_create_reference(env, argv[0], 0, &events->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, events, bare_win_ui_composition_target__on_events_finalize, nullptr, &result);
  assert(err == 0);

  return result;
}

static void
bare_win_ui_composition_target__on_rendering(bare_win_ui_composition_target_events_t *events, IInspectable const &args) {
  int err;

  auto env = events->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  auto time = std::chrono::duration<double, std::milli>(args.as<RenderingEventArgs>().RenderingTime());

  js_value_t *argv[1] = {
    bare_win_ui__from_double(env, time.count()),
  };

  bare_win_ui__emit(env, events->ctx, "_onrendering", 1, argv);

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_composition_target_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  bare_win_ui_composition_target_events_t *events;
  err = js_get_value_external(env, argv[0], (void **) &events);
  assert(err == 0);

  int32_t mask;
  if (!bare_win_ui__read_int32(env, argv[1], "mask", &mask)) return nullptr;

  try {
    if ((mask & bare_win_ui_composition_target_event_rendering) == 0) {
      events->rendering.revoke();
    } else if (!events->rendering) {
      events->rendering = CompositionTarget::Rendering(auto_revoke, [events](auto const &, IInspectable const &args) {
        bare_win_ui_composition_target__on_rendering(events, args);
      });
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}
