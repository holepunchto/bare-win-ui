#pragma once

#include <assert.h>
#include <js.h>
#include <math.h>

#include "bridging.h"

// Measuring with the control that draws the text keeps the two from disagreeing.
static thread_local TextBlock bare_win_ui_text__block = nullptr;

static uint32_t
bare_win_ui_text__hard_lines(hstring const &text) {
  uint32_t lines = 1;

  for (size_t i = 0, n = text.size(); i < n; i++) {
    if (text[i] == L'\r') {
      if (i + 1 < n && text[i + 1] == L'\n') i++;

      lines++;
    } else if (text[i] == L'\n') {
      lines++;
    }
  }

  return lines;
}

static js_value_t *
bare_win_ui_text_measure(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 4;
  js_value_t *argv[4];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 4);

  hstring text;
  if (!bare_win_ui__read_string(env, argv[0], "text", &text)) return nullptr;

  js_value_type_t type;
  err = js_typeof(env, argv[1], &type);
  assert(err == 0);

  hstring family;
  bool has_family = type != js_null && type != js_undefined;

  if (has_family && !bare_win_ui__read_string(env, argv[1], "family", &family)) return nullptr;

  double size;
  if (!bare_win_ui__read_double(env, argv[2], "size", &size)) return nullptr;

  double width;
  if (!bare_win_ui__read_double(env, argv[3], "width", &width)) return nullptr;

  double measured_width = 0, measured_height = 0, lines = 0;

  try {
    if (text.size() > 0) {
      if (bare_win_ui_text__block == nullptr) bare_win_ui_text__block = TextBlock();

      auto block = bare_win_ui_text__block;

      block.Text(text);

      // An unset size and family resolve the same defaults the drawn control
      // will, which is the whole reason measuring goes through a `TextBlock`.
      if (size > 0) block.FontSize(size);
      else block.ClearValue(TextBlock::FontSizeProperty());

      if (has_family) block.FontFamily(FontFamily(family));
      else block.ClearValue(TextBlock::FontFamilyProperty());

      block.TextWrapping(TextWrapping::NoWrap);
      block.Measure(Size(INFINITY, INFINITY));

      // `DesiredSize` is rounded, so lines are counted from the exact extent.
      auto line = block.ActualHeight() / bare_win_ui_text__hard_lines(text);

      block.TextWrapping(TextWrapping::Wrap);
      block.Measure(Size(float(width), INFINITY));

      auto desired = block.DesiredSize();

      measured_width = desired.Width;
      measured_height = desired.Height;

      if (line > 0) lines = round(block.ActualHeight() / line);
    }
  } catch (hresult_error const &error) {
    bare_win_ui__throw(env, error);

    return nullptr;
  }

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_double(env, n, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, result, name, val); \
    assert(err == 0); \
  }

  V("width", measured_width)
  V("height", measured_height)
  V("lines", lines)
#undef V

  return result;
}
