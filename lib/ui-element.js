const binding = require('../binding')
const DependencyObject = require('./dependency-object')

module.exports = exports = class WinUIUIElement extends DependencyObject {
  static _events = {
    pointerPressed: binding.UI_ELEMENT_EVENT_POINTER_PRESSED,
    pointerReleased: binding.UI_ELEMENT_EVENT_POINTER_RELEASED,
    pointerMoved: binding.UI_ELEMENT_EVENT_POINTER_MOVED,
    pointerCanceled: binding.UI_ELEMENT_EVENT_POINTER_CANCELED
  }

  get opacity() {
    return binding.uiElementOpacity(this._tag)
  }

  set opacity(value) {
    binding.uiElementOpacity(this._tag, value)
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.uiElementEvents(this)

    binding.uiElementEventMask(this._tag, this._subscription, mask)
  }

  _onpointerpressed(x, y, pointerId, deviceType) {
    return this.emit('pointerPressed', { x, y, pointerId, deviceType })
  }

  _onpointerreleased(x, y, pointerId, deviceType) {
    return this.emit('pointerReleased', { x, y, pointerId, deviceType })
  }

  _onpointermoved(x, y, pointerId, deviceType) {
    return this.emit('pointerMoved', { x, y, pointerId, deviceType })
  }

  _onpointercanceled(x, y, pointerId, deviceType) {
    return this.emit('pointerCanceled', { x, y, pointerId, deviceType })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIUIElement }
    }
  }
}
