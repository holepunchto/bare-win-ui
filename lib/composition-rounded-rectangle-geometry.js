const binding = require('../binding')
const CompositionGeometry = require('./composition-geometry')

module.exports = exports = class WinUICompositionRoundedRectangleGeometry extends (
  CompositionGeometry
) {
  get size() {
    return binding.compositionRoundedRectangleGeometrySize(this._tag)
  }

  set size(value) {
    const { x = 0, y = 0 } = value

    binding.compositionRoundedRectangleGeometrySize(this._tag, x, y)
  }

  get cornerRadius() {
    return binding.compositionRoundedRectangleGeometryCornerRadius(this._tag)
  }

  set cornerRadius(value) {
    const { x = 0, y = 0 } = value

    binding.compositionRoundedRectangleGeometryCornerRadius(this._tag, x, y)
  }

  get offset() {
    return binding.compositionRoundedRectangleGeometryOffset(this._tag)
  }

  set offset(value) {
    const { x = 0, y = 0 } = value

    binding.compositionRoundedRectangleGeometryOffset(this._tag, x, y)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionRoundedRectangleGeometry }
    }
  }
}
