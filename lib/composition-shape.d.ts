import WinUICompositionObject = require('./composition-object')

/** A shape in a shape visual, as a `CompositionShape`. */
interface WinUICompositionShape extends WinUICompositionObject {
  get offset(): { x: number; y: number }
  set offset(offset: { x?: number; y?: number })
}

declare class WinUICompositionShape {
  protected constructor()
}

export = WinUICompositionShape
