const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUICanvasPathBuilder extends WinUIObject {
  constructor() {
    super({ tag: binding.canvasPathBuilderInit() })
  }

  beginFigure(x, y) {
    binding.canvasPathBuilderBeginFigure(this._tag, x, y)
    return this
  }

  addLine(x, y) {
    binding.canvasPathBuilderAddLine(this._tag, x, y)
    return this
  }

  addCubicBezier(x1, y1, x2, y2, x, y) {
    binding.canvasPathBuilderAddCubicBezier(this._tag, x1, y1, x2, y2, x, y)
    return this
  }

  addArc(x, y, radiusX, radiusY, rotation = 0) {
    binding.canvasPathBuilderAddArc(this._tag, x, y, radiusX, radiusY, rotation)
    return this
  }

  endFigure(closed = true) {
    binding.canvasPathBuilderEndFigure(this._tag, closed)
    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICanvasPathBuilder }
    }
  }
}
