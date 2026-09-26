const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const CompositionColorBrush = require('./composition-color-brush')
const CompositionGeometricClip = require('./composition-geometric-clip')
const CompositionRoundedRectangleGeometry = require('./composition-rounded-rectangle-geometry')
const CompositionSpriteShape = require('./composition-sprite-shape')
const CompositionSurfaceBrush = require('./composition-surface-brush')
const CompositionVisualSurface = require('./composition-visual-surface')
const DropShadow = require('./drop-shadow')
const ShapeVisual = require('./shape-visual')
const SpriteVisual = require('./sprite-visual')
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

  createSpriteVisual() {
    return wrap(SpriteVisual, binding.compositorCreateSpriteVisual(this._tag))
  }

  createDropShadow() {
    return wrap(DropShadow, binding.compositorCreateDropShadow(this._tag))
  }

  createVisualSurface() {
    return wrap(CompositionVisualSurface, binding.compositorCreateVisualSurface(this._tag))
  }

  createSurfaceBrush(surface) {
    if (surface === undefined) {
      return wrap(CompositionSurfaceBrush, binding.compositorCreateSurfaceBrush(this._tag))
    }

    return wrap(
      CompositionSurfaceBrush,
      binding.compositorCreateSurfaceBrush(this._tag, adopt(surface))
    )
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

expose(exports)
