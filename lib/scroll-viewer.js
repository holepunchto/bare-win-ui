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

  get offset() {
    return binding.scrollViewerOffset(this._tag)
  }

  set offset({ x = 0, y = 0 }) {
    binding.scrollViewerOffset(this._tag, x, y)
  }

  get extent() {
    return binding.scrollViewerExtent(this._tag)
  }

  setScrollMode(horizontal, vertical) {
    binding.scrollViewerScrollMode(this._tag, horizontal, vertical)

    return this
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.scrollViewerEvents(this)

    binding.scrollViewerEventMask(this._tag, this._subscription, mask)
  }

  _onviewchanged(x, y) {
    this.emit('viewChanged', { x, y })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIScrollViewer }
    }
  }
}
