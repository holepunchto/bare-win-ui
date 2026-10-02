#pragma once

#include <assert.h>
#include <js.h>

#include "bridging.h"

static js_value_t *
bare_win_ui_run_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  js_value_t *result;

  try {
    result = bare_win_ui__from_object(env, state, Run());
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_run_text(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_string(env, run.Text());
    } else {
      hstring text;
      if (!bare_win_ui__read_string(env, argv[1], "text", &text)) return nullptr;

      run.Text(text);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_run_font_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, run.FontSize());
    } else {
      double size;
      if (!bare_win_ui__read_double(env, argv[1], "fontSize", &size)) return nullptr;

      run.FontSize(size);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// WinUI sets underline and strikethrough as one flag word.
static js_value_t *
bare_win_ui_run_text_decorations(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  int32_t decorations;
  if (!bare_win_ui__read_int32(env, argv[1], "textDecorations", &decorations)) return nullptr;

  try {
    run.TextDecorations(static_cast<Windows::UI::Text::TextDecorations>(decorations));
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return nullptr;
}

// WinUI counts character spacing in thousandths of the font size, where
// everything else here is in points, so the caller converts it.
static js_value_t *
bare_win_ui_run_character_spacing(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_int32(env, run.CharacterSpacing());
    } else {
      int32_t spacing;
      if (!bare_win_ui__read_int32(env, argv[1], "characterSpacing", &spacing)) return nullptr;

      run.CharacterSpacing(spacing);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_run_font_family(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, state, run.FontFamily());
    } else {
      FontFamily family = nullptr;
      if (bare_winrt_read_type(env, state->registry, argv[1], "fontFamily", &family) < 0) return nullptr;

      run.FontFamily(family);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

// `FontWeight` is a struct of one number, so the number crosses.
static js_value_t *
bare_win_ui_run_font_weight(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_double(env, run.FontWeight().Weight);
    } else {
      uint32_t weight;
      if (!bare_win_ui__read_uint32(env, argv[1], "fontWeight", &weight)) return nullptr;

      run.FontWeight(Windows::UI::Text::FontWeight{static_cast<uint16_t>(weight)});
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_run_font_style(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_int32(env, static_cast<int32_t>(run.FontStyle()));
    } else {
      int32_t font_style;
      if (!bare_win_ui__read_int32(env, argv[1], "fontStyle", &font_style)) return nullptr;

      run.FontStyle(static_cast<Windows::UI::Text::FontStyle>(font_style));
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}

static js_value_t *
bare_win_ui_run_foreground(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_win_ui_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  Run run = nullptr;
  if (bare_winrt_read_type(env, state->registry, argv[0], "handle", &run) < 0) return nullptr;

  js_value_t *result = nullptr;

  try {
    if (argc == 1) {
      result = bare_win_ui__from_object(env, state, run.Foreground());
    } else {
      Brush brush = nullptr;
      if (bare_winrt_read_type(env, state->registry, argv[1], "foreground", &brush) < 0) return nullptr;

      run.Foreground(brush);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  return result;
}
