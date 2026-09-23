const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const CompositionColorBrush = require('./composition-color-brush')
const CompositionGeometricClip = require('./composition-geometric-clip')
const CompositionRoundedRectangleGeometry = require('./composition-rounded-rectangle-geometry')
const CompositionSpriteShape = require('./composition-sprite-shape')
const ShapeVisual = require('./shape-visual')
const WinUIObject = require('./object')

module.exports = exports = class WinUICompositor extends WinUIObject {
  createShapeVisual() {
    return wrap(ShapeVisual, binding.compositorCreateShapeVisual(this._tag))
  }

  createSpriteShape(geometry) {
    if (geometry === undefined) {
      return wrap(CompositionSpriteShape, binding.compositorCreateSpriteShape(this._tag))
    }

    return wrap(
      CompositionSpriteShape,
      binding.compositorCreateSpriteShape(this._tag, adopt(geometry))
    )
  }

  createRoundedRectangleGeometry() {
    return wrap(
      CompositionRoundedRectangleGeometry,
      binding.compositorCreateRoundedRectangleGeometry(this._tag)
    )
  }

  createColorBrush(color) {
    if (color === undefined) {
      return wrap(CompositionColorBrush, binding.compositorCreateColorBrush(this._tag))
    }

    const { a = 255, r = 0, g = 0, b = 0 } = color

    return wrap(CompositionColorBrush, binding.compositorCreateColorBrush(this._tag, a, r, g, b))
  }

  createGeometricClip(geometry) {
    if (geometry === undefined) {
      return wrap(CompositionGeometricClip, binding.compositorCreateGeometricClip(this._tag))
    }

    return wrap(
      CompositionGeometricClip,
      binding.compositorCreateGeometricClip(this._tag, adopt(geometry))
    )
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositor }
    }
  }
}
