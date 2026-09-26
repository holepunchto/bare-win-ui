const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const CompositionBrush = require('./composition-brush')
const CompositionShadow = require('./composition-shadow')
const ContainerVisual = require('./container-visual')

module.exports = exports = class WinUISpriteVisual extends ContainerVisual {
  get brush() {
    return wrap(CompositionBrush, binding.spriteVisualBrush(this._tag))
  }

  set brush(value) {
    binding.spriteVisualBrush(this._tag, adopt(value))
  }

  get shadow() {
    return wrap(CompositionShadow, binding.spriteVisualShadow(this._tag))
  }

  set shadow(value) {
    binding.spriteVisualShadow(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUISpriteVisual }
    }
  }
}

expose(exports)
