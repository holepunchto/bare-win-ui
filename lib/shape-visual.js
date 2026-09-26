const binding = require('../binding')
const { expose } = require('./handle')
const retain = require('./retain')
const CompositionShapeCollection = require('./composition-shape-collection')
const ContainerVisual = require('./container-visual')

module.exports = exports = class WinUIShapeVisual extends ContainerVisual {
  get shapes() {
    return retain(this, '_shapes', CompositionShapeCollection, binding.shapeVisualShapes(this._tag))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIShapeVisual }
    }
  }
}

expose(exports)
