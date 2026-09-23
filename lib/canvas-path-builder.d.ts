import WinUIObject = require('./object')

/** Builds a path out of lines and curves with Win2D, as a `CanvasPathBuilder`. Turn it into a `WinUICanvasGeometry` to draw it. */
interface WinUICanvasPathBuilder extends WinUIObject {
  beginFigure(x: number, y: number): this

  addLine(x: number, y: number): this

  /** Add a curve to `x`, `y`, with the control points `x1`, `y1` and `x2`, `y2`. */
  addCubicBezier(x1: number, y1: number, x2: number, y2: number, x: number, y: number): this

  /** Add an arc to `x`, `y`. `rotation` is in radians. */
  addArc(x: number, y: number, radiusX: number, radiusY: number, rotation?: number): this

  /** End the figure, closing it unless `closed` is `false`. */
  endFigure(closed?: boolean): this
}

declare class WinUICanvasPathBuilder {
  constructor()
}

export = WinUICanvasPathBuilder
