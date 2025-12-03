#include <assert.h>
#include <bare.h>
#include <js.h>

#include "element.h"
#include "windows-app-sdk.h"

struct bare_win_ui_window_t {
  Window handle;

  js_env_t *env;
  js_ref_t *ctx;
};

static void
bare_win_ui_window__on_release(js_env_t *env, void *data, void *finalize_hint) {
  delete reinterpret_cast<bare_win_ui_window_t *>(data);
}

static js_value_t *
bare_win_ui_window_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  auto window = new bare_win_ui_window_t();

  window->env = env;

  err = js_create_reference(env, argv[0], 1, &window->ctx);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, window, bare_win_ui_window__on_release, nullptr, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui_window_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  bare_win_ui_window_t *window;
  err = js_get_value_external(env, argv[0], (void **) &window);
  assert(err == 0);

  js_value_t *result = NULL;

  if (argc == 1) {
    auto element = new bare_win_ui_element_t();

    element->handle = window->handle.Content();

    err = js_create_external(env, element, bare_win_ui_element__on_release, NULL, &result);
    assert(err == 0);
  } else {
    bare_win_ui_element_t *element;
    err = js_get_value_external(env, argv[1], (void **) &element);
    assert(err == 0);

    window->handle.Content(element->handle);
  }

  return result;
}

static js_value_t *
bare_win_ui_window_activate(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  bare_win_ui_window_t *window;
  err = js_get_value_external(env, argv[0], (void **) &window);
  assert(err == 0);

  window->handle.Activate();

  return nullptr;
}

static js_value_t *
bare_win_ui_window_close(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  bare_win_ui_window_t *window;
  err = js_get_value_external(env, argv[0], (void **) &window);
  assert(err == 0);

  window->handle.Close();

  return nullptr;
}
