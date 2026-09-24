const binding = require('../binding')
const { adopt } = require('./handle')
const retain = require('./retain')
const UIElement = require('./ui-element')
const FrameworkElement = require('./framework-element')

// A `ScrollViewer` is a `Control` and so a `FrameworkElement`, which is where
// a width and a height live. Reaching only as far as `UIElement` left it with
// no size to be given, and an element that is never sized grows to its
// content, which is the one thing a viewport must not do.
module.exports = exports = class WinUIScrollViewer extends FrameworkElement {
  static SCROLL_MODE = {
    DISABLED: binding.SCROLL_VIEWER_SCROLL_MODE_DISABLED,
    ENABLED: binding.SCROLL_VIEWER_SCROLL_MODE_ENABLED,
    AUTO: binding.SCROLL_VIEWER_SCROLL_MODE_AUTO
  }

  static SCROLL_BAR_VISIBILITY = {
    DISABLED: binding.SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_DISABLED,
    AUTO: binding.SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_AUTO,
    HIDDEN: binding.SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_HIDDEN,
    VISIBLE: binding.SCROLL_VIEWER_SCROLL_BAR_VISIBILITY_VISIBLE
  }

  static _events = {
    viewChanged: binding.SCROLL_VIEWER_EVENT_VIEW_CHANGED
  }

  _init() {
    return binding.scrollViewerInit()
  }

  get content() {
    return retain(this, '_content', UIElement, binding.scrollViewerContent(this._tag))
  }

  set content(value) {
    binding.scrollViewerContent(this._tag, value === null ? null : adopt(value))

    this._content = value
  }

  get horizontalOffset() {
    return binding.scrollViewerHorizontalOffset(this._tag)
  }

  get verticalOffset() {
    return binding.scrollViewerVerticalOffset(this._tag)
  }

  get extentWidth() {
    return binding.scrollViewerExtentWidth(this._tag)
  }

  get extentHeight() {
    return binding.scrollViewerExtentHeight(this._tag)
  }

  get viewportWidth() {
    return binding.scrollViewerViewportWidth(this._tag)
  }

  get viewportHeight() {
    return binding.scrollViewerViewportHeight(this._tag)
  }

  get scrollableWidth() {
    return binding.scrollViewerScrollableWidth(this._tag)
  }

  get scrollableHeight() {
    return binding.scrollViewerScrollableHeight(this._tag)
  }

  get horizontalScrollMode() {
    return binding.scrollViewerHorizontalScrollMode(this._tag)
  }

  set horizontalScrollMode(mode) {
    binding.scrollViewerHorizontalScrollMode(this._tag, mode)
  }

  get verticalScrollMode() {
    return binding.scrollViewerVerticalScrollMode(this._tag)
  }

  set verticalScrollMode(mode) {
    binding.scrollViewerVerticalScrollMode(this._tag, mode)
  }

  get horizontalScrollBarVisibility() {
    return binding.scrollViewerHorizontalScrollBarVisibility(this._tag)
  }

  set horizontalScrollBarVisibility(visibility) {
    binding.scrollViewerHorizontalScrollBarVisibility(this._tag, visibility)
  }

  get verticalScrollBarVisibility() {
    return binding.scrollViewerVerticalScrollBarVisibility(this._tag)
  }

  set verticalScrollBarVisibility(visibility) {
    binding.scrollViewerVerticalScrollBarVisibility(this._tag, visibility)
  }

  changeView(horizontalOffset, verticalOffset, zoomFactor = null, disableAnimation = false) {
    return binding.scrollViewerChangeView(
      this._tag,
      horizontalOffset,
      verticalOffset,
      zoomFactor,
      disableAnimation
    )
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.scrollViewerEvents(this)

    binding.scrollViewerEventMask(this._tag, this._subscription, mask)
  }

  _onviewchanged(isIntermediate) {
    this.emit('viewChanged', { isIntermediate })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIScrollViewer }
    }
  }
}
