const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const DependencyObject = require('./dependency-object')
const WinUIInputCursor = require('./input-cursor')
const WinUIXamlRoot = require('./xaml-root')
const WinUIGeneralTransform = require('./general-transform')

module.exports = exports = class WinUIUIElement extends DependencyObject {
  static _events = {
    pointerPressed: binding.UI_ELEMENT_EVENT_POINTER_PRESSED,
    pointerReleased: binding.UI_ELEMENT_EVENT_POINTER_RELEASED,
    pointerMoved: binding.UI_ELEMENT_EVENT_POINTER_MOVED,
    pointerCanceled: binding.UI_ELEMENT_EVENT_POINTER_CANCELED
  }

  transformToVisual(target) {
    return wrap(WinUIGeneralTransform, binding.uiElementTransformToVisual(this._tag, target._tag))
  }

  get xamlRoot() {
    return wrap(WinUIXamlRoot, binding.uiElementXamlRoot(this._tag))
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

  // The event object is returned so the binding can read what the listener set
  // on it.
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
