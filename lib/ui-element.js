const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const DependencyObject = require('./dependency-object')
const WinUIInputCursor = require('./input-cursor')

module.exports = exports = class WinUIUIElement extends DependencyObject {
  static _events = {
    pointerPressed: binding.UI_ELEMENT_EVENT_POINTER_PRESSED,
    pointerReleased: binding.UI_ELEMENT_EVENT_POINTER_RELEASED,
    pointerMoved: binding.UI_ELEMENT_EVENT_POINTER_MOVED,
    pointerCanceled: binding.UI_ELEMENT_EVENT_POINTER_CANCELED
  }

  get isHitTestVisible() {
    return binding.uiElementIsHitTestVisible(this._tag)
  }

  set isHitTestVisible(value) {
    binding.uiElementIsHitTestVisible(this._tag, value)
  }

  get protectedCursor() {
    return wrap(WinUIInputCursor, binding.uiElementProtectedCursor(this._tag))
  }

  set protectedCursor(value) {
    binding.uiElementProtectedCursor(this._tag, value === null ? null : adopt(value))
  }

  get opacity() {
    return binding.uiElementOpacity(this._tag)
  }

  set opacity(value) {
    binding.uiElementOpacity(this._tag, value)
  }

  releasePointerCaptures() {
    binding.uiElementReleasePointerCaptures(this._tag)

    return this
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.uiElementEvents(this)

    binding.uiElementEventMask(this._tag, this._subscription, mask)
  }

  // A routed event carries on to the parent unless a handler says it was
  // handled, which is what `handled` on the event is for, and a gesture
  // follows the pointer out of the element only if something asks it to, which
  // is what `capturePointer` is for. Setting either is the listener's call, as
  // it is in XAML, and the event is handed back for the binding to read them.
  //
  // `PointerMoved` is raised for a pointer merely over the element as well as
  // one pressed on it, which is what `isInContact` tells apart.
  _onpointer(name, x, y, pointerId, deviceType, isInContact) {
    const args = {
      x,
      y,
      pointerId,
      deviceType,
      isInContact,
      handled: false,
      capturePointer: false
    }

    this.emit(name, args)

    return args
  }

  _onpointerpressed(x, y, pointerId, deviceType, isInContact) {
    return this._onpointer('pointerPressed', x, y, pointerId, deviceType, isInContact)
  }

  _onpointerreleased(x, y, pointerId, deviceType, isInContact) {
    return this._onpointer('pointerReleased', x, y, pointerId, deviceType, isInContact)
  }

  _onpointermoved(x, y, pointerId, deviceType, isInContact) {
    return this._onpointer('pointerMoved', x, y, pointerId, deviceType, isInContact)
  }

  _onpointercanceled(x, y, pointerId, deviceType, isInContact) {
    return this._onpointer('pointerCanceled', x, y, pointerId, deviceType, isInContact)
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
