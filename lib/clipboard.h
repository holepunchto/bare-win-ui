#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_clipboard_get_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, Clipboard::GetContent());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  } catch (...) {
    bare_win_ui__throw(env, hresult_error(E_FAIL, L"The clipboard could not be read"));

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_clipboard_set_content(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  DataPackage package = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "package", &package) < 0) return nullptr;

  try {
    Clipboard::SetContent(package);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  } catch (...) {
    bare_win_ui__throw(env, hresult_error(E_FAIL, L"The clipboard could not be written"));
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_clipboard_clear(js_env_t *env, js_callback_info_t *info) {
  try {
    Clipboard::Clear();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  } catch (...) {
    bare_win_ui__throw(env, hresult_error(E_FAIL, L"The clipboard could not be cleared"));
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_clipboard_flush(js_env_t *env, js_callback_info_t *info) {
  try {
    Clipboard::Flush();
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  } catch (...) {
    bare_win_ui__throw(env, hresult_error(E_FAIL, L"The clipboard could not be flushed"));
  }

  return nullptr;
}
