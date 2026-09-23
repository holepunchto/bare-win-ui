const binding = require('../binding')
const Brush = require('./brush')

module.exports = exports = class WinUISolidColorBrush extends Brush {
  _init(opts) {
    const { color = null } = opts

    if (color === null) return binding.solidColorBrushInit()

    const { a = 255, r = 0, g = 0, b = 0 } = color

    return binding.solidColorBrushInit(a, r, g, b)
  }

  get color() {
    return binding.solidColorBrushColor(this._tag)
  }

  set color(value) {
    const { a = 255, r = 0, g = 0, b = 0 } = value

    binding.solidColorBrushColor(this._tag, a, r, g, b)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUISolidColorBrush }
    }
  }
}
