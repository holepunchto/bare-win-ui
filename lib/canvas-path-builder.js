const binding = require('../binding')
const { adopt, expose } = require('./handle')
const WinUIObject = require('./object')

// What a path is made of, in the order Win2D takes it. Nothing here is drawn
// with: a builder becomes a geometry and a geometry becomes a composition
// path, which is the only way to give the compositor a shape it has no
// geometry type for.
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

expose(exports)
