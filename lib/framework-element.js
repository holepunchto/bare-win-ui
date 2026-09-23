const binding = require('../binding')
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
