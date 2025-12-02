#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include "lib/window.h"

static js_value_t *
bare_win_ui_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, nullptr, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("windowInit", bare_win_ui_window_init)
  V("windowActivate", bare_win_ui_window_activate)
  V("windowClose", bare_win_ui_window_close)
#undef V

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_int32(env, n, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }
#undef V

  return exports;
}

BARE_MODULE(bare_win_ui, bare_win_ui_exports)
