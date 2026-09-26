const binding = require('../binding')
const { adopt, expose } = require('./handle')
const CompositionGeometry = require('./composition-geometry')

module.exports = exports = class WinUICompositionPathGeometry extends CompositionGeometry {
  set path(value) {
    binding.compositionPathGeometryPath(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionPathGeometry }
    }
  }
}

expose(exports)
