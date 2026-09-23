const binding = require('../binding')
const DependencyObject = require('./dependency-object')

module.exports = exports = class WinUIUIElement extends DependencyObject {
  get opacity() {
    return binding.uiElementOpacity(this._tag)
  }

  set opacity(value) {
    binding.uiElementOpacity(this._tag, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIUIElement }
    }
  }
}
