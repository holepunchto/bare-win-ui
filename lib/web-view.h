#include <assert.h>
#include <bare.h>
#include <js.h>

#include "windows-app-sdk.h"

struct bare_win_ui_web_view_t {
  WebView2 handle;

  js_env_t *env;
  js_ref_t *ctx;
  js_ref_t *on_ready;
};

static void
bare_win_ui_web_view__on_release(js_env_t *env, void *data, void *finalize_hint) {
  int err;

  auto self = reinterpret_cast<bare_win_ui_web_view_t *>(data);

  err = js_delete_reference(env, self->on_ready);
  assert(err == 0);

  err = js_delete_reference(env, self->ctx);
  assert(err == 0);

  delete self;
}

static void
bare_win_ui_web_view__on_ready(bare_win_ui_web_view_t *self) {
  int err;

  auto env = self->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *ctx;
  err = js_get_reference_value(env, self->ctx, &ctx);
  assert(err == 0);

  js_value_t *on_ready;
  err = js_get_reference_value(env, self->on_ready, &on_ready);
  assert(err == 0);

  err = js_call_function(env, ctx, on_ready, 0, nullptr, nullptr);
  (void) err;

  err = js_close_handle_scope(env, scope);
  assert(err == 0);
}

static js_value_t *
bare_win_ui_web_view_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  auto web_view = new bare_win_ui_web_view_t();

  web_view->env = env;

  err = js_create_reference(env, argv[0], 1, &web_view->ctx);
  assert(err == 0);

  err = js_create_reference(env, argv[1], 1, &web_view->on_ready);
  assert(err == 0);

  web_view->handle.CoreWebView2Initialized([=](auto &, auto &) {
    bare_win_ui_web_view__on_ready(web_view);
  });

  js_value_t *result;
  err = js_create_external(env, web_view, bare_win_ui_web_view__on_release, nullptr, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui_web_view_ensure_ready(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  web_view->handle.EnsureCoreWebView2Async();

  return nullptr;
}

static js_value_t *
bare_win_ui_web_view_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  js_value_t *result = nullptr;

  if (argc == 1) {
    err = js_create_double(env, web_view->handle.Width(), &result);
    assert(err == 0);
  } else {
    double width;
    err = js_get_value_double(env, argv[1], &width);
    assert(err == 0);

    web_view->handle.Width(width);
  }

  return result;
}

static js_value_t *
bare_win_ui_web_view_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  js_value_t *result = nullptr;

  if (argc == 1) {
    err = js_create_double(env, web_view->handle.Height(), &result);
    assert(err == 0);
  } else {
    double height;
    err = js_get_value_double(env, argv[1], &height);
    assert(err == 0);

    web_view->handle.Height(height);
  }

  return result;
}

static js_value_t *
bare_win_ui_web_view_source(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  js_value_t *result = nullptr;

  if (argc == 1) {
    auto source = web_view->handle.Source().AbsoluteUri();

    err = js_create_string_utf16le(env, reinterpret_cast<const utf16_t *>(source.data()), source.size(), &result);
    assert(err == 0);
  } else {
    size_t len;
    err = js_get_value_string_utf16le(env, argv[1], nullptr, 0, &len);
    assert(err == 0);

    std::vector<wchar_t> uri(len);
    err = js_get_value_string_utf16le(env, argv[1], reinterpret_cast<utf16_t *>(uri.data()), len, nullptr);
    assert(err == 0);

    web_view->handle.Source(Uri(hstring(uri.data(), len)));
  }

  return result;
}

static js_value_t *
bare_win_ui_web_view_navigate(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  size_t len;
  err = js_get_value_string_utf16le(env, argv[1], nullptr, 0, &len);
  assert(err == 0);

  std::vector<wchar_t> uri(len);
  err = js_get_value_string_utf16le(env, argv[1], reinterpret_cast<utf16_t *>(uri.data()), len, nullptr);
  assert(err == 0);

  auto core = web_view->handle.CoreWebView2();

  assert(core);

  core.Navigate(hstring(uri.data(), len));

  return nullptr;
}

static js_value_t *
bare_win_ui_web_view_navigate_to_string(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  size_t len;
  err = js_get_value_string_utf16le(env, argv[1], nullptr, 0, &len);
  assert(err == 0);

  std::vector<wchar_t> html(len);
  err = js_get_value_string_utf16le(env, argv[1], reinterpret_cast<utf16_t *>(html.data()), len, nullptr);
  assert(err == 0);

  auto core = web_view->handle.CoreWebView2();

  assert(core);

  core.NavigateToString(hstring(html.data(), len));

  return nullptr;
}

static js_value_t *
bare_win_ui_web_view_open_dev_tools_window(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  bare_win_ui_web_view_t *web_view;
  err = js_get_value_external(env, argv[0], (void **) &web_view);
  assert(err == 0);

  auto core = web_view->handle.CoreWebView2();

  assert(core);

  core.OpenDevToolsWindow();

  return nullptr;
}
