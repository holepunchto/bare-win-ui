#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

enum {
  bare_win_ui_data_package_operation_none = int(DataPackageOperation::None),
  bare_win_ui_data_package_operation_copy = int(DataPackageOperation::Copy),
  bare_win_ui_data_package_operation_move = int(DataPackageOperation::Move),
  bare_win_ui_data_package_operation_link = int(DataPackageOperation::Link),
};

static js_value_t *
bare_win_ui_data_package_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, DataPackage());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_data_package_set_text(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  DataPackage package = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &package) < 0) return nullptr;

  hstring text;
  if (!bare_win_ui__read_string(env, argv[1], "text", &text)) return nullptr;

  try {
    package.SetText(text);
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);
  }

  return nullptr;
}

static js_value_t *
bare_win_ui_data_package_requested_operation(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  DataPackage package = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &package) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      err = js_create_int32(env, int32_t(package.RequestedOperation()), &result);
      assert(err == 0);
    } else {
      int32_t operation;
      if (!bare_win_ui__read_int32(env, argv[1], "operation", &operation)) return nullptr;

      package.RequestedOperation(DataPackageOperation(operation));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_data_package_get_view(js_env_t *env, js_callback_info_t *info) {
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
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &package) < 0) return nullptr;

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, package.GetView());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
