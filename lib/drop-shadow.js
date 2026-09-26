const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const CompositionBrush = require('./composition-brush')
const CompositionShadow = require('./composition-shadow')

module.exports = exports = class WinUIDropShadow extends CompositionShadow {
  get color() {
    return binding.dropShadowColor(this._tag)
  }

  set color(value) {
    const { a = 255, r = 0, g = 0, b = 0 } = value

    binding.dropShadowColor(this._tag, a, r, g, b)
  }

  get offset() {
    return binding.dropShadowOffset(this._tag)
  }

  set offset(value) {
    const { x = 0, y = 0, z = 0 } = value

    binding.dropShadowOffset(this._tag, x, y, z)
  }

  get blurRadius() {
    return binding.dropShadowBlurRadius(this._tag)
  }

  set blurRadius(value) {
    binding.dropShadowBlurRadius(this._tag, value)
  }

  get opacity() {
    return binding.dropShadowOpacity(this._tag)
  }

  set opacity(value) {
    binding.dropShadowOpacity(this._tag, value)
  }

  get mask() {
    return wrap(CompositionBrush, binding.dropShadowMask(this._tag))
  }

  set mask(value) {
    binding.dropShadowMask(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIDropShadow }
    }
  }
}

expose(exports)
