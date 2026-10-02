import WinUIContainerVisual = require('./container-visual')
import WinUICompositionShapeCollection = require('./composition-shape-collection')

/** A visual that draws shapes, as a `ShapeVisual`. */
interface WinUIShapeVisual extends WinUIContainerVisual {
  readonly shapes: WinUICompositionShapeCollection
}

declare class WinUIShapeVisual {
  protected constructor()
}

export = WinUIShapeVisual
