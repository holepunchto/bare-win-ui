#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include "lib/bridging.h"
#include "lib/canvas.h"
#include "lib/composition-color-brush.h"
#include "lib/composition-geometric-clip.h"
#include "lib/composition-object.h"
#include "lib/composition-rounded-rectangle-geometry.h"
#include "lib/composition-shape.h"
#include "lib/composition-shape-collection.h"
#include "lib/composition-sprite-shape.h"
#include "lib/compositor.h"
#include "lib/element-composition-preview.h"
#include "lib/font-family.h"
#include "lib/framework-element.h"
#include "lib/headless.h"
#include "lib/package-manager.h"
#include "lib/panel.h"
#include "lib/shape-visual.h"
#include "lib/solid-color-brush.h"
#include "lib/text.h"
#include "lib/text-block.h"
#include "lib/ui-element.h"
#include "lib/ui-element-collection.h"
#include "lib/visual.h"
#include "lib/web-view2.h"
#include "lib/window.h"

static js_value_t *
bare_win_ui_exports(js_env_t *env, js_value_t *exports) {
  int err;

  err = bare_win_ui__headless_init(env);
  if (err < 0) return nullptr;

#define T(name, fn, typed, ...) \
  { \
    static int args[] = {__VA_ARGS__}; \
    static const js_callback_signature_t signature = {0, js_undefined, sizeof(args) / sizeof(args[0]), args}; \
    js_value_t *val; \
    err = js_create_typed_function(env, name, -1, fn, &signature, reinterpret_cast<const void *>(typed), nullptr, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, nullptr, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("claim", bare_winrt_claim)
  V("wrapper", bare_winrt_wrapper)
  V("registrySize", bare_winrt_registry_size)
  V("handle", bare_winrt_handle)
  V("adopt", bare_winrt_adopt)

  V("packageManagerInit", bare_win_ui_package_manager_init)
  V("packageManagerAddPackage", bare_win_ui_package_manager_add_package)

  T("uiElementOpacity", bare_win_ui_ui_element_opacity, bare_win_ui_ui_element_opacity_typed, js_object, js_uint32, js_float64)

  T("frameworkElementWidth", bare_win_ui_framework_element_width, bare_win_ui_framework_element_width_typed, js_object, js_uint32, js_float64)
  T("frameworkElementHeight", bare_win_ui_framework_element_height, bare_win_ui_framework_element_height_typed, js_object, js_uint32, js_float64)
  V("frameworkElementActualWidth", bare_win_ui_framework_element_actual_width)
  V("frameworkElementActualHeight", bare_win_ui_framework_element_actual_height)
  V("frameworkElementParent", bare_win_ui_framework_element_parent)

  V("panelChildren", bare_win_ui_panel_children)
  V("panelBackground", bare_win_ui_panel_background)

  V("uiElementCollectionSize", bare_win_ui_ui_element_collection_size)
  V("uiElementCollectionGetAt", bare_win_ui_ui_element_collection_get_at)
  V("uiElementCollectionIndexOf", bare_win_ui_ui_element_collection_index_of)
  V("uiElementCollectionAppend", bare_win_ui_ui_element_collection_append)
  V("uiElementCollectionInsertAt", bare_win_ui_ui_element_collection_insert_at)
  V("uiElementCollectionRemoveAt", bare_win_ui_ui_element_collection_remove_at)
  V("uiElementCollectionClear", bare_win_ui_ui_element_collection_clear)

  V("canvasInit", bare_win_ui_canvas_init)
  V("canvasGetLeft", bare_win_ui_canvas_get_left)
  T("canvasSetLeft", bare_win_ui_canvas_set_left, bare_win_ui_canvas_set_left_typed, js_object, js_uint32, js_float64)
  V("canvasGetTop", bare_win_ui_canvas_get_top)
  T("canvasSetTop", bare_win_ui_canvas_set_top, bare_win_ui_canvas_set_top_typed, js_object, js_uint32, js_float64)

  V("textBlockInit", bare_win_ui_text_block_init)
  V("textBlockText", bare_win_ui_text_block_text)
  V("textBlockFontSize", bare_win_ui_text_block_font_size)
  V("textBlockFontFamily", bare_win_ui_text_block_font_family)
  V("textBlockForeground", bare_win_ui_text_block_foreground)
  V("textBlockTextAlignment", bare_win_ui_text_block_text_alignment)
  V("textBlockTextWrapping", bare_win_ui_text_block_text_wrapping)

  V("fontFamilyInit", bare_win_ui_font_family_init)
  V("fontFamilySource", bare_win_ui_font_family_source)

  V("solidColorBrushInit", bare_win_ui_solid_color_brush_init)
  V("solidColorBrushColor", bare_win_ui_solid_color_brush_color)

  V("windowInit", bare_win_ui_window_init)
  V("windowTitle", bare_win_ui_window_title)
  V("windowContent", bare_win_ui_window_content)
  V("windowBounds", bare_win_ui_window_bounds)
  V("windowActivate", bare_win_ui_window_activate)
  V("windowClose", bare_win_ui_window_close)
  V("windowResize", bare_win_ui_window_resize)
  V("windowResizeClient", bare_win_ui_window_resize_client)
  V("windowEvents", bare_win_ui_window_events)
  V("windowEventMask", bare_win_ui_window_event_mask)

  V("webView2Init", bare_win_ui_web_view2_init)
  V("webView2Source", bare_win_ui_web_view2_source)
  V("webView2Navigate", bare_win_ui_web_view2_navigate)
  V("webView2NavigateToString", bare_win_ui_web_view2_navigate_to_string)
  V("webView2OpenDevToolsWindow", bare_win_ui_web_view2_open_dev_tools_window)

  V("compositorCreateShapeVisual", bare_win_ui_compositor_create_shape_visual)
  V("compositorCreateSpriteShape", bare_win_ui_compositor_create_sprite_shape)
  V("compositorCreateRoundedRectangleGeometry", bare_win_ui_compositor_create_rounded_rectangle_geometry)
  V("compositorCreateColorBrush", bare_win_ui_compositor_create_color_brush)
  V("compositorCreateGeometricClip", bare_win_ui_compositor_create_geometric_clip)

  V("compositionObjectCompositor", bare_win_ui_composition_object_compositor)

  T("visualSize", bare_win_ui_visual_size, bare_win_ui_visual_size_typed, js_object, js_uint32, js_float64, js_float64)
  V("visualClip", bare_win_ui_visual_clip)

  V("shapeVisualShapes", bare_win_ui_shape_visual_shapes)

  V("compositionShapeOffset", bare_win_ui_composition_shape_offset)

  V("compositionShapeCollectionSize", bare_win_ui_composition_shape_collection_size)
  V("compositionShapeCollectionGetAt", bare_win_ui_composition_shape_collection_get_at)
  V("compositionShapeCollectionIndexOf", bare_win_ui_composition_shape_collection_index_of)
  V("compositionShapeCollectionAppend", bare_win_ui_composition_shape_collection_append)
  V("compositionShapeCollectionInsertAt", bare_win_ui_composition_shape_collection_insert_at)
  V("compositionShapeCollectionRemoveAt", bare_win_ui_composition_shape_collection_remove_at)
  V("compositionShapeCollectionClear", bare_win_ui_composition_shape_collection_clear)

  V("compositionSpriteShapeGeometry", bare_win_ui_composition_sprite_shape_geometry)
  V("compositionSpriteShapeFillBrush", bare_win_ui_composition_sprite_shape_fill_brush)
  V("compositionSpriteShapeStrokeBrush", bare_win_ui_composition_sprite_shape_stroke_brush)
  V("compositionSpriteShapeStrokeThickness", bare_win_ui_composition_sprite_shape_stroke_thickness)

  T("compositionRoundedRectangleGeometrySize", bare_win_ui_composition_rounded_rectangle_geometry_size, bare_win_ui_composition_rounded_rectangle_geometry_size_typed, js_object, js_uint32, js_float64, js_float64)
  V("compositionRoundedRectangleGeometryCornerRadius", bare_win_ui_composition_rounded_rectangle_geometry_corner_radius)
  V("compositionRoundedRectangleGeometryOffset", bare_win_ui_composition_rounded_rectangle_geometry_offset)

  V("compositionColorBrushColor", bare_win_ui_composition_color_brush_color)

  V("compositionGeometricClipGeometry", bare_win_ui_composition_geometric_clip_geometry)

  V("elementCompositionPreviewGetElementVisual", bare_win_ui_element_composition_preview_get_element_visual)
  V("elementCompositionPreviewGetElementChildVisual", bare_win_ui_element_composition_preview_get_element_child_visual)
  V("elementCompositionPreviewSetElementChildVisual", bare_win_ui_element_composition_preview_set_element_child_visual)

  V("textMeasure", bare_win_ui_text_measure)

#undef V
#undef T

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_int32(env, int32_t(n), &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("TEXT_ALIGNMENT_CENTER", TextAlignment::Center)
  V("TEXT_ALIGNMENT_LEFT", TextAlignment::Left)
  V("TEXT_ALIGNMENT_START", TextAlignment::Start)
  V("TEXT_ALIGNMENT_RIGHT", TextAlignment::Right)
  V("TEXT_ALIGNMENT_END", TextAlignment::End)
  V("TEXT_ALIGNMENT_JUSTIFY", TextAlignment::Justify)
  V("TEXT_ALIGNMENT_DETECT_FROM_CONTENT", TextAlignment::DetectFromContent)

  V("TEXT_WRAPPING_NO_WRAP", TextWrapping::NoWrap)
  V("TEXT_WRAPPING_WRAP", TextWrapping::Wrap)
  V("TEXT_WRAPPING_WRAP_WHOLE_WORDS", TextWrapping::WrapWholeWords)

  V("WINDOW_EVENT_SIZE_CHANGED", bare_win_ui_window_event_size_changed)
#undef V

  return exports;
}

BARE_MODULE(bare_win_ui, bare_win_ui_exports)
