const binding = require('../binding')
const { expose } = require('./handle')
const CompositionBrush = require('./composition-brush')

module.exports = exports = class WinUICompositionColorBrush extends CompositionBrush {
  get color() {
    return binding.compositionColorBrushColor(this._tag)
  }

  set color(value) {
    const { a = 255, r = 0, g = 0, b = 0 } = value

    binding.compositionColorBrushColor(this._tag, a, r, g, b)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionColorBrush }
    }
  }
}

expose(exports)
