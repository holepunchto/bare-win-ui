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
#include "lib/canvas-geometry.h"
#include "lib/canvas-path-builder.h"
#include "lib/composition-path.h"
#include "lib/composition-shape.h"
#include "lib/composition-shape-collection.h"
#include "lib/composition-sprite-shape.h"
#include "lib/composition-visual-surface.h"
#include "lib/compositor.h"
#include "lib/drop-shadow.h"
#include "lib/element-composition-preview.h"
#include "lib/sprite-visual.h"
#include "lib/font-family.h"
#include "lib/inline-collection.h"
#include "lib/input-system-cursor.h"
#include "lib/framework-element.h"
#include "lib/headless.h"
#include "lib/image.h"
#include "lib/bitmap-image.h"
#include "lib/package-manager.h"
#include "lib/panel.h"
#include "lib/run.h"
#include "lib/shape-visual.h"
#include "lib/solid-color-brush.h"
#include "lib/text.h"
#include "lib/control.h"
#include "lib/password-box.h"
#include "lib/progress-ring.h"
#include "lib/toggle-switch.h"
#include "lib/text-box.h"
#include "lib/text-block.h"
#include "lib/ui-element.h"
#include "lib/ui-element-collection.h"
#include "lib/visual.h"
#include "lib/web-view2.h"
#include "lib/scroll-viewer.h"
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

  V("uiElementIsHitTestVisible", bare_win_ui_ui_element_is_hit_test_visible)
  V("uiElementProtectedCursor", bare_win_ui_ui_element_protected_cursor)
  V("uiElementReleasePointerCaptures", bare_win_ui_ui_element_release_pointer_captures)
  T("uiElementOpacity", bare_win_ui_ui_element_opacity, bare_win_ui_ui_element_opacity_typed, js_object, js_uint32, js_float64)
  V("uiElementMeasure", bare_win_ui_ui_element_measure)
  V("uiElementDesiredSize", bare_win_ui_ui_element_desired_size)

  T("frameworkElementWidth", bare_win_ui_framework_element_width, bare_win_ui_framework_element_width_typed, js_object, js_uint32, js_float64)
  T("frameworkElementHeight", bare_win_ui_framework_element_height, bare_win_ui_framework_element_height_typed, js_object, js_uint32, js_float64)
  V("frameworkElementResource", bare_win_ui_framework_element_resource)
  V("frameworkElementMinWidth", bare_win_ui_framework_element_min_width)
  V("frameworkElementMinHeight", bare_win_ui_framework_element_min_height)
  V("frameworkElementActualWidth", bare_win_ui_framework_element_actual_width)
  V("frameworkElementActualHeight", bare_win_ui_framework_element_actual_height)
  V("frameworkElementHorizontalAlignment", bare_win_ui_framework_element_horizontal_alignment)
  V("frameworkElementVerticalAlignment", bare_win_ui_framework_element_vertical_alignment)
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
  V("canvasSetZIndex", bare_win_ui_canvas_set_z_index)
  V("canvasGetLeft", bare_win_ui_canvas_get_left)
  T("canvasSetLeft", bare_win_ui_canvas_set_left, bare_win_ui_canvas_set_left_typed, js_object, js_uint32, js_float64)
  V("canvasGetTop", bare_win_ui_canvas_get_top)
  T("canvasSetTop", bare_win_ui_canvas_set_top, bare_win_ui_canvas_set_top_typed, js_object, js_uint32, js_float64)

  V("imageInit", bare_win_ui_image_init)
  V("imageSource", bare_win_ui_image_source)
  V("imageStretch", bare_win_ui_image_stretch)
  V("imageEvents", bare_win_ui_image_events)
  V("imageEventMask", bare_win_ui_image_event_mask)

  V("bitmapImageInit", bare_win_ui_bitmap_image_init)
  V("bitmapImageUriSource", bare_win_ui_bitmap_image_uri_source)
  V("bitmapSourcePixelWidth", bare_win_ui_bitmap_source_pixel_width)
  V("bitmapSourcePixelHeight", bare_win_ui_bitmap_source_pixel_height)

  V("controlFocus", bare_win_ui_control_focus)
  V("controlIsEnabled", bare_win_ui_control_is_enabled)
  V("controlBackground", bare_win_ui_control_background)
  V("controlUseSystemFocusVisuals", bare_win_ui_control_use_system_focus_visuals)
  V("controlForeground", bare_win_ui_control_foreground)
  V("controlBorderBrush", bare_win_ui_control_border_brush)
  V("controlBorderThickness", bare_win_ui_control_border_thickness)
  V("controlTemplateChild", bare_win_ui_control_template_child)
  V("controlPadding", bare_win_ui_control_padding)
  V("controlHorizontalContentAlignment", bare_win_ui_control_horizontal_content_alignment)
  V("controlVerticalContentAlignment", bare_win_ui_control_vertical_content_alignment)
  V("controlCornerRadius", bare_win_ui_control_corner_radius)
  V("focusManagerTryMoveFocus", bare_win_ui_focus_manager_try_move_focus)

  V("textBoxInit", bare_win_ui_text_box_init)
  V("textBoxEvents", bare_win_ui_text_box_events)
  V("textBoxEventMask", bare_win_ui_text_box_event_mask)
  V("textBoxText", bare_win_ui_text_box_text)
  V("textBoxPlaceholderText", bare_win_ui_text_box_placeholder_text)
  V("textBoxIsReadOnly", bare_win_ui_text_box_is_read_only)
  V("textBoxAcceptsReturn", bare_win_ui_text_box_accepts_return)
  V("textBoxIsSpellCheckEnabled", bare_win_ui_text_box_is_spell_check_enabled)
  V("textBoxSelectionStart", bare_win_ui_text_box_selection_start)
  V("textBoxSelectionLength", bare_win_ui_text_box_selection_length)
  V("textBoxTextWrapping", bare_win_ui_text_box_text_wrapping)
  V("textBoxInputScope", bare_win_ui_text_box_input_scope)

  V("progressRingInit", bare_win_ui_progress_ring_init)
  V("progressRingIsActive", bare_win_ui_progress_ring_is_active)

  V("toggleSwitchInit", bare_win_ui_toggle_switch_init)
  V("toggleSwitchEvents", bare_win_ui_toggle_switch_events)
  V("toggleSwitchEventMask", bare_win_ui_toggle_switch_event_mask)
  V("toggleSwitchIsOn", bare_win_ui_toggle_switch_is_on)
  V("toggleSwitchContent", bare_win_ui_toggle_switch_content)

  V("passwordBoxInit", bare_win_ui_password_box_init)
  V("passwordBoxEvents", bare_win_ui_password_box_events)
  V("passwordBoxEventMask", bare_win_ui_password_box_event_mask)
  V("passwordBoxPasswordRevealMode", bare_win_ui_password_box_password_reveal_mode)
  V("passwordBoxPassword", bare_win_ui_password_box_password)
  V("passwordBoxPlaceholderText", bare_win_ui_password_box_placeholder_text)

  V("textBlockInit", bare_win_ui_text_block_init)
  V("textBlockText", bare_win_ui_text_block_text)
  V("textBlockFontSize", bare_win_ui_text_block_font_size)
  V("textBlockLineHeight", bare_win_ui_text_block_line_height)
  V("textBlockFontFamily", bare_win_ui_text_block_font_family)
  V("textBlockForeground", bare_win_ui_text_block_foreground)
  V("textBlockTextAlignment", bare_win_ui_text_block_text_alignment)
  V("textBlockMaxLines", bare_win_ui_text_block_max_lines)
  V("textBlockTextTrimming", bare_win_ui_text_block_text_trimming)
  V("textBoxTextAlignment", bare_win_ui_text_box_text_alignment)
  V("textBlockTextWrapping", bare_win_ui_text_block_text_wrapping)
  V("textBlockInlines", bare_win_ui_text_block_inlines)

  V("inlineCollectionSize", bare_win_ui_inline_collection_size)
  V("inlineCollectionAppend", bare_win_ui_inline_collection_append)
  V("inlineCollectionClear", bare_win_ui_inline_collection_clear)

  V("runInit", bare_win_ui_run_init)
  V("runText", bare_win_ui_run_text)
  V("runFontSize", bare_win_ui_run_font_size)
  V("runCharacterSpacing", bare_win_ui_run_character_spacing)
  V("runTextDecorations", bare_win_ui_run_text_decorations)
  V("runFontFamily", bare_win_ui_run_font_family)
  V("runFontWeight", bare_win_ui_run_font_weight)
  V("runFontStyle", bare_win_ui_run_font_style)
  V("runForeground", bare_win_ui_run_foreground)

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
  V("scrollViewerInit", bare_win_ui_scroll_viewer_init)
  V("scrollViewerContent", bare_win_ui_scroll_viewer_content)
  V("scrollViewerHorizontalOffset", bare_win_ui_scroll_viewer_horizontal_offset)
  V("scrollViewerVerticalOffset", bare_win_ui_scroll_viewer_vertical_offset)
  V("scrollViewerExtentWidth", bare_win_ui_scroll_viewer_extent_width)
  V("scrollViewerExtentHeight", bare_win_ui_scroll_viewer_extent_height)
  V("scrollViewerViewportWidth", bare_win_ui_scroll_viewer_viewport_width)
  V("scrollViewerViewportHeight", bare_win_ui_scroll_viewer_viewport_height)
  V("scrollViewerScrollableWidth", bare_win_ui_scroll_viewer_scrollable_width)
  V("scrollViewerScrollableHeight", bare_win_ui_scroll_viewer_scrollable_height)
  V("scrollViewerChangeView", bare_win_ui_scroll_viewer_change_view)
  V("scrollViewerHorizontalScrollMode", bare_win_ui_scroll_viewer_horizontal_scroll_mode)
  V("scrollViewerVerticalScrollMode", bare_win_ui_scroll_viewer_vertical_scroll_mode)
  V("scrollViewerHorizontalScrollBarVisibility", bare_win_ui_scroll_viewer_horizontal_scroll_bar_visibility)
  V("scrollViewerVerticalScrollBarVisibility", bare_win_ui_scroll_viewer_vertical_scroll_bar_visibility)
  V("scrollViewerEvents", bare_win_ui_scroll_viewer_events)
  V("scrollViewerEventMask", bare_win_ui_scroll_viewer_event_mask)

  V("uiElementEvents", bare_win_ui_ui_element_events)
  V("uiElementEventMask", bare_win_ui_ui_element_event_mask)
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
  V("compositorCreatePathGeometry", bare_win_ui_compositor_create_path_geometry)

  V("canvasPathBuilderInit", bare_win_ui_canvas_path_builder_init)
  V("canvasPathBuilderBeginFigure", bare_win_ui_canvas_path_builder_begin_figure)
  V("canvasPathBuilderAddLine", bare_win_ui_canvas_path_builder_add_line)
  V("canvasPathBuilderAddCubicBezier", bare_win_ui_canvas_path_builder_add_cubic_bezier)
  V("canvasPathBuilderAddArc", bare_win_ui_canvas_path_builder_add_arc)
  V("canvasPathBuilderEndFigure", bare_win_ui_canvas_path_builder_end_figure)

  V("canvasGeometryCreatePath", bare_win_ui_canvas_geometry_create_path)

  V("inputSystemCursorCreate", bare_win_ui_input_system_cursor_create)
  V("inputSystemCursorCursorShape", bare_win_ui_input_system_cursor_cursor_shape)

  V("compositionPathInit", bare_win_ui_composition_path_init)
  V("compositionPathGeometryPath", bare_win_ui_composition_path_geometry_path)
  V("compositorCreateSpriteVisual", bare_win_ui_compositor_create_sprite_visual)
  V("compositorCreateDropShadow", bare_win_ui_compositor_create_drop_shadow)
  V("compositorCreateVisualSurface", bare_win_ui_compositor_create_visual_surface)
  V("compositorCreateSurfaceBrush", bare_win_ui_compositor_create_surface_brush)

  V("compositionObjectCompositor", bare_win_ui_composition_object_compositor)

  T("visualSize", bare_win_ui_visual_size, bare_win_ui_visual_size_typed, js_object, js_uint32, js_float64, js_float64)
  V("visualClip", bare_win_ui_visual_clip)
  V("visualTransformMatrix", bare_win_ui_visual_transform_matrix)

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
  V("compositionSpriteShapeStrokeDashArray", bare_win_ui_composition_sprite_shape_stroke_dash_array)
  V("compositionSpriteShapeStrokeThickness", bare_win_ui_composition_sprite_shape_stroke_thickness)

  T("compositionRoundedRectangleGeometrySize", bare_win_ui_composition_rounded_rectangle_geometry_size, bare_win_ui_composition_rounded_rectangle_geometry_size_typed, js_object, js_uint32, js_float64, js_float64)
  V("compositionRoundedRectangleGeometryCornerRadius", bare_win_ui_composition_rounded_rectangle_geometry_corner_radius)
  V("compositionRoundedRectangleGeometryOffset", bare_win_ui_composition_rounded_rectangle_geometry_offset)

  V("compositionColorBrushColor", bare_win_ui_composition_color_brush_color)

  V("compositionVisualSurfaceSourceVisual", bare_win_ui_composition_visual_surface_source_visual)
  V("compositionVisualSurfaceSourceSize", bare_win_ui_composition_visual_surface_source_size)
  V("compositionVisualSurfaceSourceOffset", bare_win_ui_composition_visual_surface_source_offset)

  V("spriteVisualBrush", bare_win_ui_sprite_visual_brush)
  V("spriteVisualShadow", bare_win_ui_sprite_visual_shadow)

  V("dropShadowColor", bare_win_ui_drop_shadow_color)
  V("dropShadowOffset", bare_win_ui_drop_shadow_offset)
  V("dropShadowBlurRadius", bare_win_ui_drop_shadow_blur_radius)
  V("dropShadowOpacity", bare_win_ui_drop_shadow_opacity)
  V("dropShadowMask", bare_win_ui_drop_shadow_mask)

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

  V("TEXT_TRIMMING_NONE", TextTrimming::None)
  V("TEXT_TRIMMING_CLIP", TextTrimming::Clip)
  V("TEXT_TRIMMING_WORD_ELLIPSIS", TextTrimming::WordEllipsis)
  V("TEXT_TRIMMING_CHARACTER_ELLIPSIS", TextTrimming::CharacterEllipsis)
  V("INPUT_SYSTEM_CURSOR_SHAPE_ARROW", InputSystemCursorShape::Arrow)
  V("INPUT_SYSTEM_CURSOR_SHAPE_CROSS", InputSystemCursorShape::Cross)
  V("INPUT_SYSTEM_CURSOR_SHAPE_HAND", InputSystemCursorShape::Hand)
  V("INPUT_SYSTEM_CURSOR_SHAPE_HELP", InputSystemCursorShape::Help)
  V("INPUT_SYSTEM_CURSOR_SHAPE_IBEAM", InputSystemCursorShape::IBeam)
  V("INPUT_SYSTEM_CURSOR_SHAPE_SIZE_ALL", InputSystemCursorShape::SizeAll)
  V("INPUT_SYSTEM_CURSOR_SHAPE_SIZE_NORTHEAST_SOUTHWEST", InputSystemCursorShape::SizeNortheastSouthwest)
  V("INPUT_SYSTEM_CURSOR_SHAPE_SIZE_NORTH_SOUTH", InputSystemCursorShape::SizeNorthSouth)
  V("INPUT_SYSTEM_CURSOR_SHAPE_SIZE_NORTHWEST_SOUTHEAST", InputSystemCursorShape::SizeNorthwestSoutheast)
  V("INPUT_SYSTEM_CURSOR_SHAPE_SIZE_WEST_EAST", InputSystemCursorShape::SizeWestEast)
  V("INPUT_SYSTEM_CURSOR_SHAPE_UNIVERSAL_NO", InputSystemCursorShape::UniversalNo)
  V("INPUT_SYSTEM_CURSOR_SHAPE_UP_ARROW", InputSystemCursorShape::UpArrow)
  V("INPUT_SYSTEM_CURSOR_SHAPE_WAIT", InputSystemCursorShape::Wait)
  V("INPUT_SYSTEM_CURSOR_SHAPE_PIN", InputSystemCursorShape::Pin)
  V("INPUT_SYSTEM_CURSOR_SHAPE_PERSON", InputSystemCursorShape::Person)
  V("INPUT_SYSTEM_CURSOR_SHAPE_APP_STARTING", InputSystemCursorShape::AppStarting)

  V("HORIZONTAL_ALIGNMENT_LEFT", HorizontalAlignment::Left)
  V("HORIZONTAL_ALIGNMENT_CENTER", HorizontalAlignment::Center)
  V("HORIZONTAL_ALIGNMENT_RIGHT", HorizontalAlignment::Right)
  V("HORIZONTAL_ALIGNMENT_STRETCH", HorizontalAlignment::Stretch)

  V("VERTICAL_ALIGNMENT_TOP", VerticalAlignment::Top)
  V("VERTICAL_ALIGNMENT_CENTER", VerticalAlignment::Center)
  V("VERTICAL_ALIGNMENT_BOTTOM", VerticalAlignment::Bottom)
  V("VERTICAL_ALIGNMENT_STRETCH", VerticalAlignment::Stretch)

  V("TEXT_ALIGNMENT_CENTER", TextAlignment::Center)
  V("TEXT_ALIGNMENT_LEFT", TextAlignment::Left)
  V("TEXT_ALIGNMENT_START", TextAlignment::Start)
  V("TEXT_ALIGNMENT_RIGHT", TextAlignment::Right)
  V("TEXT_ALIGNMENT_END", TextAlignment::End)
  V("TEXT_ALIGNMENT_JUSTIFY", TextAlignment::Justify)
  V("TEXT_ALIGNMENT_DETECT_FROM_CONTENT", TextAlignment::DetectFromContent)

  V("FONT_STYLE_NORMAL", Windows::UI::Text::FontStyle::Normal)
  V("FONT_STYLE_OBLIQUE", Windows::UI::Text::FontStyle::Oblique)
  V("FONT_STYLE_ITALIC", Windows::UI::Text::FontStyle::Italic)

  V("TEXT_BOX_EVENT_TEXT_CHANGING", bare_win_ui_text_box_event_text_changing)
  V("TEXT_BOX_EVENT_TEXT_CHANGED", bare_win_ui_text_box_event_text_changed)
  V("TEXT_BOX_EVENT_SELECTION_CHANGED", bare_win_ui_text_box_event_selection_changed)
  V("TEXT_BOX_EVENT_GOT_FOCUS", bare_win_ui_text_box_event_got_focus)
  V("TEXT_BOX_EVENT_LOST_FOCUS", bare_win_ui_text_box_event_lost_focus)
  V("TEXT_BOX_EVENT_KEY_DOWN", bare_win_ui_text_box_event_key_down)
  V("TEXT_BOX_EVENT_LOADED", bare_win_ui_text_box_event_loaded)

  V("TEXT_DECORATIONS_NONE", Windows::UI::Text::TextDecorations::None)
  V("TEXT_DECORATIONS_UNDERLINE", Windows::UI::Text::TextDecorations::Underline)
  V("TEXT_DECORATIONS_STRIKETHROUGH", Windows::UI::Text::TextDecorations::Strikethrough)

  V("TOGGLE_SWITCH_EVENT_TOGGLED", bare_win_ui_toggle_switch_event_toggled)
  V("TOGGLE_SWITCH_EVENT_LOADED", bare_win_ui_toggle_switch_event_loaded)

  V("PASSWORD_BOX_EVENT_PASSWORD_CHANGED", bare_win_ui_password_box_event_password_changed)
  V("PASSWORD_BOX_EVENT_GOT_FOCUS", bare_win_ui_password_box_event_got_focus)
  V("PASSWORD_BOX_EVENT_LOST_FOCUS", bare_win_ui_password_box_event_lost_focus)
  V("PASSWORD_BOX_EVENT_LOADED", bare_win_ui_password_box_event_loaded)

  V("PASSWORD_REVEAL_MODE_PEEK", PasswordRevealMode::Peek)
  V("PASSWORD_REVEAL_MODE_HIDDEN", PasswordRevealMode::Hidden)
  V("PASSWORD_REVEAL_MODE_VISIBLE", PasswordRevealMode::Visible)

  V("FOCUS_STATE_UNFOCUSED", FocusState::Unfocused)
  V("FOCUS_STATE_POINTER", FocusState::Pointer)
  V("FOCUS_STATE_KEYBOARD", FocusState::Keyboard)
  V("FOCUS_STATE_PROGRAMMATIC", FocusState::Programmatic)

  V("FOCUS_NAVIGATION_DIRECTION_NEXT", FocusNavigationDirection::Next)
  V("FOCUS_NAVIGATION_DIRECTION_PREVIOUS", FocusNavigationDirection::Previous)
  V("FOCUS_NAVIGATION_DIRECTION_UP", FocusNavigationDirection::Up)
  V("FOCUS_NAVIGATION_DIRECTION_DOWN", FocusNavigationDirection::Down)
  V("FOCUS_NAVIGATION_DIRECTION_LEFT", FocusNavigationDirection::Left)
  V("FOCUS_NAVIGATION_DIRECTION_RIGHT", FocusNavigationDirection::Right)
  V("FOCUS_NAVIGATION_DIRECTION_NONE", FocusNavigationDirection::None)

  V("TEXT_WRAPPING_NO_WRAP", TextWrapping::NoWrap)
  V("TEXT_WRAPPING_WRAP", TextWrapping::Wrap)
  V("TEXT_WRAPPING_WRAP_WHOLE_WORDS", TextWrapping::WrapWholeWords)

  V("IMAGE_EVENT_IMAGE_OPENED", bare_win_ui_image_event_image_opened)
  V("IMAGE_EVENT_IMAGE_FAILED", bare_win_ui_image_event_image_failed)

  V("STRETCH_NONE", Stretch::None)
  V("STRETCH_FILL", Stretch::Fill)
  V("STRETCH_UNIFORM", Stretch::Uniform)
  V("STRETCH_UNIFORM_TO_FILL", Stretch::UniformToFill)

  V("SCROLL_VIEWER_EVENT_VIEW_CHANGED", bare_win_ui_scroll_viewer_event_view_changed)

  V("SCROLL_VIEWER_SCROLL_MODE_DISABLED", ScrollMode::Disabled)
  V("SCROLL_VIEWER_SCROLL_MODE_ENABLED", ScrollMode::Enabled)
  V("SCROLL_VIEWER_SCROLL_MODE_AUTO", ScrollMode::Auto)

  V("SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_DISABLED", ScrollBarVisibility::Disabled)
  V("SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_AUTO", ScrollBarVisibility::Auto)
  V("SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_HIDDEN", ScrollBarVisibility::Hidden)
  V("SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_VISIBLE", ScrollBarVisibility::Visible)

  V("UI_ELEMENT_EVENT_POINTER_PRESSED", bare_win_ui_ui_element_event_pointer_pressed)
  V("UI_ELEMENT_EVENT_POINTER_RELEASED", bare_win_ui_ui_element_event_pointer_released)
  V("UI_ELEMENT_EVENT_POINTER_MOVED", bare_win_ui_ui_element_event_pointer_moved)
  V("UI_ELEMENT_EVENT_POINTER_CANCELED", bare_win_ui_ui_element_event_pointer_canceled)

  V("POINTER_DEVICE_TYPE_TOUCH", int32_t(Windows::Devices::Input::PointerDeviceType::Touch))
  V("POINTER_DEVICE_TYPE_PEN", int32_t(Windows::Devices::Input::PointerDeviceType::Pen))
  V("POINTER_DEVICE_TYPE_MOUSE", int32_t(Windows::Devices::Input::PointerDeviceType::Mouse))

  V("WINDOW_EVENT_SIZE_CHANGED", bare_win_ui_window_event_size_changed)
#undef V

  return exports;
}

BARE_MODULE(bare_win_ui, bare_win_ui_exports)
