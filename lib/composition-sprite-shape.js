const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const CompositionBrush = require('./composition-brush')
const CompositionGeometry = require('./composition-geometry')
const CompositionShape = require('./composition-shape')

module.exports = exports = class WinUICompositionSpriteShape extends CompositionShape {
  get geometry() {
    return wrap(CompositionGeometry, binding.compositionSpriteShapeGeometry(this._tag))
  }

  set geometry(value) {
    binding.compositionSpriteShapeGeometry(this._tag, adopt(value))
  }

  get fillBrush() {
    return wrap(CompositionBrush, binding.compositionSpriteShapeFillBrush(this._tag))
  }

  set fillBrush(value) {
    binding.compositionSpriteShapeFillBrush(this._tag, adopt(value))
  }

  get strokeBrush() {
    return wrap(CompositionBrush, binding.compositionSpriteShapeStrokeBrush(this._tag))
  }

  set strokeBrush(value) {
    binding.compositionSpriteShapeStrokeBrush(this._tag, adopt(value))
  }

  get strokeThickness() {
    return binding.compositionSpriteShapeStrokeThickness(this._tag)
  }

  set strokeThickness(value) {
    binding.compositionSpriteShapeStrokeThickness(this._tag, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionSpriteShape }
    }
  }
}
