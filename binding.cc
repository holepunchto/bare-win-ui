#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include "lib/web-view.h"
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
  V("windowTitle", bare_win_ui_window_title)
  V("windowContent", bare_win_ui_window_content)
  V("windowActivate", bare_win_ui_window_activate)
  V("windowClose", bare_win_ui_window_close)
  V("windowResize", bare_win_ui_window_resize)
  V("windowResizeClient", bare_win_ui_window_resize_client)

  V("webViewInit", bare_win_ui_web_view_init)
  V("webViewEnsureReady", bare_win_ui_web_view_ensure_ready)
  V("webViewWidth", bare_win_ui_web_view_width)
  V("webViewHeight", bare_win_ui_web_view_height)
  V("webViewSource", bare_win_ui_web_view_source)
  V("webViewNavigate", bare_win_ui_web_view_navigate)
  V("webViewNavigateToString", bare_win_ui_web_view_navigate_to_string)
  V("webViewOpenDevToolsWindow", bare_win_ui_web_view_open_dev_tools_window)
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
