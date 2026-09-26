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

  get parent() {
    return wrap(DependencyObject, binding.frameworkElementParent(this._tag))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIFrameworkElement }
    }
  }
}

expose(exports)
