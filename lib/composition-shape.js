const binding = require('../binding')
const { expose } = require('./handle')
const CompositionObject = require('./composition-object')

module.exports = exports = class WinUICompositionShape extends CompositionObject {
  get offset() {
    return binding.compositionShapeOffset(this._tag)
  }

  set offset(value) {
    const { x = 0, y = 0 } = value

    binding.compositionShapeOffset(this._tag, x, y)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionShape }
    }
  }
}

expose(exports)
