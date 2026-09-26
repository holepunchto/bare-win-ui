const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const CompositionObject = require('./composition-object')
const Visual = require('./visual')

module.exports = exports = class WinUICompositionVisualSurface extends CompositionObject {
  get sourceVisual() {
    return wrap(Visual, binding.compositionVisualSurfaceSourceVisual(this._tag))
  }

  set sourceVisual(value) {
    binding.compositionVisualSurfaceSourceVisual(this._tag, adopt(value))
  }

  get sourceSize() {
    return binding.compositionVisualSurfaceSourceSize(this._tag)
  }

  set sourceSize(value) {
    const { x = 0, y = 0 } = value

    binding.compositionVisualSurfaceSourceSize(this._tag, x, y)
  }

  get sourceOffset() {
    return binding.compositionVisualSurfaceSourceOffset(this._tag)
  }

  set sourceOffset(value) {
    const { x = 0, y = 0 } = value

    binding.compositionVisualSurfaceSourceOffset(this._tag, x, y)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionVisualSurface }
    }
  }
}

expose(exports)
