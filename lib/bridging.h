#pragma once

#include <assert.h>
#include <js.h>
#include <string>
#include <utf.h>

#include "windows-app-sdk.h"

#include "registry.h"

static bool
bare_win_ui__read_number(js_env_t *env, js_value_t *value, const char *name) {
  int err;

  js_value_type_t type;
  err = js_typeof(env, value, &type);
  assert(err == 0);

  if (type == js_number) return true;

  err = js_throw_type_errorf(env, nullptr, "Expected a number for '%s'", name);
  assert(err == 0);

  return false;
}

static bool
bare_win_ui__read_int32(js_env_t *env, js_value_t *value, const char *name, int32_t *result) {
  if (!bare_win_ui__read_number(env, value, name)) return false;

  int err = js_get_value_int32(env, value, result);
  assert(err == 0);

  return true;
}

static bool
bare_win_ui__read_uint32(js_env_t *env, js_value_t *value, const char *name, uint32_t *result) {
  if (!bare_win_ui__read_number(env, value, name)) return false;

  int err = js_get_value_uint32(env, value, result);
  assert(err == 0);

  return true;
}

static bool
bare_win_ui__read_double(js_env_t *env, js_value_t *value, const char *name, double *result) {
  if (!bare_win_ui__read_number(env, value, name)) return false;

  int err = js_get_value_double(env, value, result);
  assert(err == 0);

  return true;
}

static bool
bare_win_ui__read_float(js_env_t *env, js_value_t *value, const char *name, float *result) {
  double n;
  if (!bare_win_ui__read_double(env, value, name, &n)) return false;

  *result = float(n);

  return true;
}

static bool
bare_win_ui__read_byte(js_env_t *env, js_value_t *value, const char *name, uint8_t *result) {
  uint32_t n;
  if (!bare_win_ui__read_uint32(env, value, name, &n)) return false;

  if (n > 255) {
    int err = js_throw_range_errorf(env, nullptr, "Expected '%s' to be between 0 and 255", name);
    assert(err == 0);

    return false;
  }

  *result = uint8_t(n);

  return true;
}

static bool
bare_win_ui__read_string(js_env_t *env, js_value_t *value, const char *name, hstring *result) {
  int err;

  js_value_type_t type;
  err = js_typeof(env, value, &type);
  assert(err == 0);

  if (type != js_string) {
    err = js_throw_type_errorf(env, nullptr, "Expected a string for '%s'", name);
    assert(err == 0);

    return false;
  }

  size_t len;
  err = js_get_value_string_utf16le(env, value, nullptr, 0, &len);
  assert(err == 0);

  std::wstring data(len, L'\0');

  err = js_get_value_string_utf16le(env, value, reinterpret_cast<utf16_t *>(data.data()), len, nullptr);
  assert(err == 0);

  *result = hstring(data);

  return true;
}

static bool
bare_win_ui__read_bool(js_env_t *env, js_value_t *value, const char *name, bool *result) {
  int err;

  js_value_type_t type;
  err = js_typeof(env, value, &type);
  assert(err == 0);

  if (type != js_boolean) {
    err = js_throw_type_errorf(env, nullptr, "Expected a boolean for '%s'", name);
    assert(err == 0);

    return false;
  }

  err = js_get_value_bool(env, value, result);
  assert(err == 0);

  return true;
}

template <typename T>
static bool
bare_win_ui__read_nullable(js_env_t *env, js_value_t *value, const char *name, T *result) {
  int err;

  js_value_type_t type;
  err = js_typeof(env, value, &type);
  assert(err == 0);

  if (type == js_null || type == js_undefined) {
    *result = nullptr;

    return true;
  }

  return bare_winrt__read_type<T>(env, value, name, result) == 0;
}

// A WinRT method taking an `IReference` is taking a value a caller is free to
// leave alone, which is what null means on the way in.
template <typename T>
static bool
bare_win_ui__read_optional(js_env_t *env, js_value_t *value, const char *name, IReference<T> *result) {
  int err;

  js_value_type_t type;
  err = js_typeof(env, value, &type);
  assert(err == 0);

  if (type == js_null || type == js_undefined) {
    *result = nullptr;

    return true;
  }

  double number;
  if (!bare_win_ui__read_double(env, value, name, &number)) return false;

  *result = static_cast<T>(number);

  return true;
}

static js_value_t *
bare_win_ui__from_object(js_env_t *env, IInspectable const &object) {
  int err;

  js_value_t *result;

  if (object == nullptr) {
    err = js_get_null(env, &result);
    assert(err == 0);
  } else {
    err = js_create_uint32(env, bare_winrt__tag(object), &result);
    assert(err == 0);
  }

  return result;
}

static js_value_t *
bare_win_ui__from_string(js_env_t *env, hstring const &string) {
  int err;

  js_value_t *result;
  err = js_create_string_utf16le(env, reinterpret_cast<const utf16_t *>(string.data()), string.size(), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui__from_double(js_env_t *env, double value) {
  int err;

  js_value_t *result;
  err = js_create_double(env, value, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui__from_point(js_env_t *env, double x, double y) {
  int err;

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  err = js_set_named_property(env, result, "x", bare_win_ui__from_double(env, x));
  assert(err == 0);

  err = js_set_named_property(env, result, "y", bare_win_ui__from_double(env, y));
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui__from_int32(js_env_t *env, int32_t value) {
  int err;

  js_value_t *result;
  err = js_create_int32(env, value, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_win_ui__from_fields(js_env_t *env, std::initializer_list<std::pair<const char *, double>> fields) {
  int err;

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  for (auto const &[name, n] : fields) {
    err = js_set_named_property(env, result, name, bare_win_ui__from_double(env, n));
    assert(err == 0);
  }

  return result;
}

static js_value_t *
bare_win_ui__from_rect(js_env_t *env, Rect const &rect) {
  return bare_win_ui__from_fields(env, {{"x", rect.X}, {"y", rect.Y}, {"width", rect.Width}, {"height", rect.Height}});
}

static js_value_t *
bare_win_ui__from_float2(js_env_t *env, Numerics::float2 const &vector) {
  return bare_win_ui__from_fields(env, {{"x", vector.x}, {"y", vector.y}});
}

static js_value_t *
bare_win_ui__from_color(js_env_t *env, winrt::Windows::UI::Color const &color) {
  return bare_win_ui__from_fields(env, {{"a", color.A}, {"r", color.R}, {"g", color.G}, {"b", color.B}});
}

// An exception unwinding into the JS engine terminates the process.
static void
bare_win_ui__throw(js_env_t *env, hresult_error const &error) {
  int err;

  auto message = to_string(error.message());

  err = js_throw_errorf(env, nullptr, "%s (0x%08X)", message.c_str(), uint32_t(error.code()));
  assert(err == 0);
}

static void
bare_win_ui__emit(js_env_t *env, js_ref_t *ctx, const char *name, size_t argc, js_value_t *const *argv) {
  int err;

  js_value_t *receiver;
  err = js_get_reference_value(env, ctx, &receiver);
  assert(err == 0);

  if (receiver == nullptr) return;

  js_value_t *fn;
  err = js_get_named_property(env, receiver, name, &fn);
  assert(err == 0);

  err = js_call_function(env, receiver, fn, argc, argv, nullptr);
  (void) err;
}
