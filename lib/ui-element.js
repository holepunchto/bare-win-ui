const binding = require('../binding')
const { expose } = require('./handle')
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

  // A routed event carries on to the parent unless a handler says it was
  // handled, which is what `handled` on the event is for. Whether to set it is
  // the listener's call, as it is in XAML.
  _onpointer(name, x, y, pointerId, deviceType) {
    const args = { x, y, pointerId, deviceType, handled: false }

    this.emit(name, args)

    return args.handled
  }

  _onpointerpressed(x, y, pointerId, deviceType) {
    return this._onpointer('pointerPressed', x, y, pointerId, deviceType)
  }

  _onpointerreleased(x, y, pointerId, deviceType) {
    return this._onpointer('pointerReleased', x, y, pointerId, deviceType)
  }

  _onpointermoved(x, y, pointerId, deviceType) {
    return this._onpointer('pointerMoved', x, y, pointerId, deviceType)
  }

  _onpointercanceled(x, y, pointerId, deviceType) {
    return this._onpointer('pointerCanceled', x, y, pointerId, deviceType)
  }

  measure({ width, height }) {
    binding.uiElementMeasure(this._tag, width, height)

    return this
  }

  get desiredSize() {
    return binding.uiElementDesiredSize(this._tag)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIUIElement }
    }
  }
}

expose(exports)
