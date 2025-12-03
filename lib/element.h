#include <js.h>

#include "windows-app-sdk.h"

struct bare_win_ui_element_t {
  UIElement handle = nullptr;
};

static void
bare_win_ui_element__on_release(js_env_t *env, void *data, void *finalize_hint) {
  delete reinterpret_cast<bare_win_ui_element_t *>(data);
}
