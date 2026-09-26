const binding = require('../binding')
const { expose } = require('./handle')
const wrap = require('./wrap')
const DependencyObject = require('./dependency-object')
const UIElement = require('./ui-element')

module.exports = exports = class WinUIFrameworkElement extends UIElement {
  get width() {
    return binding.frameworkElementWidth(this._tag)
  }

  set width(value) {
    binding.frameworkElementWidth(this._tag, value)
  }

  get height() {
    return binding.frameworkElementHeight(this._tag)
  }

  set height(value) {
    binding.frameworkElementHeight(this._tag, value)
  }

  resource(key, value) {
    binding.frameworkElementResource(this._tag, key, value)

    return this
  }

  set minWidth(value) {
    binding.frameworkElementMinWidth(this._tag, value)
  }

  set minHeight(value) {
    binding.frameworkElementMinHeight(this._tag, value)
  }

  get actualWidth() {
    return binding.frameworkElementActualWidth(this._tag)
  }

  get actualHeight() {
    return binding.frameworkElementActualHeight(this._tag)
  }

  get horizontalAlignment() {
    return binding.frameworkElementHorizontalAlignment(this._tag)
  }

  set horizontalAlignment(value) {
    binding.frameworkElementHorizontalAlignment(this._tag, value)
  }

  get verticalAlignment() {
    return binding.frameworkElementVerticalAlignment(this._tag)
  }

  set verticalAlignment(value) {
    binding.frameworkElementVerticalAlignment(this._tag, value)
  }

  get parent() {
    return wrap(DependencyObject, binding.frameworkElementParent(this._tag))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIFrameworkElement }
    }
  }
}

// A `VerticalAlignment` is what an element is placed by and what a control
// puts its content by, so both reach for these.
exports.HORIZONTAL_ALIGNMENT = {
  LEFT: binding.HORIZONTAL_ALIGNMENT_LEFT,
  CENTER: binding.HORIZONTAL_ALIGNMENT_CENTER,
  RIGHT: binding.HORIZONTAL_ALIGNMENT_RIGHT,
  STRETCH: binding.HORIZONTAL_ALIGNMENT_STRETCH
}

exports.VERTICAL_ALIGNMENT = {
  TOP: binding.VERTICAL_ALIGNMENT_TOP,
  CENTER: binding.VERTICAL_ALIGNMENT_CENTER,
  BOTTOM: binding.VERTICAL_ALIGNMENT_BOTTOM,
  STRETCH: binding.VERTICAL_ALIGNMENT_STRETCH
}

expose(exports)
