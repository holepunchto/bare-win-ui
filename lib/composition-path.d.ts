import WinUIObject = require('./object')
import WinUICanvasGeometry = require('./canvas-geometry')

/** A path for a composition path geometry, as a `CompositionPath`. */
interface WinUICompositionPath extends WinUIObject {}

declare class WinUICompositionPath {
  constructor(geometry: WinUICanvasGeometry)
}

export = WinUICompositionPath
