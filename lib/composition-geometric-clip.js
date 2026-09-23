const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const CompositionGeometry = require('./composition-geometry')
const CompositionClip = require('./composition-clip')

module.exports = exports = class WinUICompositionGeometricClip extends CompositionClip {
  get geometry() {
    return wrap(CompositionGeometry, binding.compositionGeometricClipGeometry(this._tag))
  }

  set geometry(value) {
    binding.compositionGeometricClipGeometry(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionGeometricClip }
    }
  }
}
