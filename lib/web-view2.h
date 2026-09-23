#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"
#include "headless.h"

struct bare_win_ui_web_view2_ready_t {
  js_env_t *env;
  js_ref_t *ctx;
  js_ref_t *on_ready;
};

static void
bare_win_ui_web_view2__on_ready(bare_win_ui_web_view2_ready_t *ready, hresult error) {
  int err;

  auto env = ready->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *ctx;
  err = js_get_reference_value(env, ready->ctx, &ctx);
  assert(err == 0);

  if (ctx != nullptr) {
    js_value_t *on_ready;
    err = js_get_reference_value(env, ready->on_ready, &on_ready);
    assert(err == 0);

    js_value_t *argv[1];

    if (error == S_OK) {
      err = js_get_null(env, &argv[0]);
      assert(err == 0);
    } else {
      argv[0] = bare_win_ui__from_string(env, hresult_error(error).message());
    }

    err = js_call_function(env, ctx, on_ready, 1, argv, nullptr);
    (void) err;
  }

  err = js_close_handle_scope(env, scope);
  assert(err == 0);

  err = js_delete_reference(env, ready->on_ready);
  assert(err == 0);

  err = js_delete_reference(env, ready->ctx);
  assert(err == 0);

  delete ready;

  bare_win_ui__headless_release();
}

static js_value_t *
bare_win_ui_web_view2_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  js_value_t *result;

  try {
    WebView2 web_view;

    result = bare_win_ui__from_object(env, web_view);

    auto ready = new bare_win_ui_web_view2_ready_t();

    ready->env = env;

    err = js_create_reference(env, argv[0], 0, &ready->ctx);
    assert(err == 0);

    err = js_create_reference(env, argv[1], 1, &ready->on_ready);
    assert(err == 0);

    auto dispatcher = DispatcherQueue::GetForCurrentThread();

    bare_win_ui__headless_hold();

    web_view.EnsureCoreWebView2Async().Completed([=](auto const &operation, auto const &) {
      auto error = operation.ErrorCode();

      dispatcher.TryEnqueue([=] {
        bare_win_ui_web_view2__on_ready(ready, error);
      });
    });
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_web_view2_source(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  WebView2 web_view = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &web_view) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      auto source = web_view.Source();

      if (source == nullptr) {
        err = js_get_null(env, &result);
        assert(err == 0);
      } else {
        result = bare_win_ui__from_string(env, source.AbsoluteUri());
      }
    } else {
      hstring uri;
      if (!bare_win_ui__read_string(env, argv[1], "uri", &uri)) return nullptr;

      web_view.Source(Uri(uri));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static bool
bare_win_ui_web_view2__core(js_env_t *env, js_value_t *value, CoreWebView2 *result) {
  int err;

  WebView2 web_view = nullptr;
  if (bare_winrt__read_type(env, value, "handle", &web_view) < 0) return false;

  *result = web_view.CoreWebView2();

  if (*result == nullptr) {
    err = js_throw_error(env, nullptr, "The web view is not ready");
    assert(err == 0);

    return false;
  }

  return true;
}

static js_value_t *
bare_win_ui_web_view2_navigate(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  hstring uri;
  if (!bare_win_ui__read_string(env, argv[1], "uri", &uri)) return nullptr;

  try {
    CoreWebView2 core = nullptr;
    if (!bare_win_ui_web_view2__core(env, argv[0], &core)) return nullptr;

    core.Navigate(uri);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_web_view2_navigate_to_string(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  hstring html;
  if (!bare_win_ui__read_string(env, argv[1], "html", &html)) return nullptr;

  try {
    CoreWebView2 core = nullptr;
    if (!bare_win_ui_web_view2__core(env, argv[0], &core)) return nullptr;

    core.NavigateToString(html);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_web_view2_open_dev_tools_window(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  try {
    CoreWebView2 core = nullptr;
    if (!bare_win_ui_web_view2__core(env, argv[0], &core)) return nullptr;

    core.OpenDevToolsWindow();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}
