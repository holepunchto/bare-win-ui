import WinUIObject = require('./object')
import WinUICanvasPathBuilder = require('./canvas-path-builder')

/** A Win2D geometry, as a `CanvasGeometry`. Wrap it in a `WinUICompositionPath` to draw it. */
interface WinUICanvasGeometry extends WinUIObject {}

declare class WinUICanvasGeometry {
  protected constructor()

  static createPath(builder: WinUICanvasPathBuilder): WinUICanvasGeometry
}

export = WinUICanvasGeometry
