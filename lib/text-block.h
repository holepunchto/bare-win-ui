#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_text_block_init(js_env_t *env, js_callback_info_t *info) {
  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, TextBlock());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_text(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_string(env, text_block.Text());
    } else {
      hstring text;
      if (!bare_win_ui__read_string(env, argv[1], "text", &text)) return nullptr;

      text_block.Text(text);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_font_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, text_block.FontSize());
    } else {
      double font_size;
      if (!bare_win_ui__read_double(env, argv[1], "font_size", &font_size)) return nullptr;

      text_block.FontSize(font_size);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_font_family(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, text_block.FontFamily());
    } else {
      FontFamily font_family = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "font_family", &font_family)) return nullptr;

      text_block.FontFamily(font_family);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_foreground(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, text_block.Foreground());
    } else {
      Brush foreground = nullptr;
      if (!bare_win_ui__read_nullable(env, argv[1], "foreground", &foreground)) return nullptr;

      text_block.Foreground(foreground);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_text_alignment(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_int32(env, int32_t(text_block.TextAlignment()));
    } else {
      int32_t text_alignment;
      if (!bare_win_ui__read_int32(env, argv[1], "text_alignment", &text_alignment)) return nullptr;

      text_block.TextAlignment(TextAlignment(text_alignment));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_text_wrapping(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_int32(env, int32_t(text_block.TextWrapping()));
    } else {
      int32_t text_wrapping;
      if (!bare_win_ui__read_int32(env, argv[1], "text_wrapping", &text_wrapping)) return nullptr;

      text_block.TextWrapping(TextWrapping(text_wrapping));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_text_block_inlines(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  TextBlock text_block = nullptr;
  if (bare_winrt__read_type(env, argv[0], "handle", &text_block) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    result = bare_win_ui__from_object(env, text_block.Inlines());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
