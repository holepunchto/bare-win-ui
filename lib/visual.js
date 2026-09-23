const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const CompositionClip = require('./composition-clip')
const CompositionObject = require('./composition-object')

module.exports = exports = class WinUIVisual extends CompositionObject {
  get size() {
    return binding.visualSize(this._tag)
  }

  set size(value) {
    const { x = 0, y = 0 } = value

    binding.visualSize(this._tag, x, y)
  }

  get clip() {
    return wrap(CompositionClip, binding.visualClip(this._tag))
  }

  set clip(value) {
    binding.visualClip(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIVisual }
    }
  }
}
