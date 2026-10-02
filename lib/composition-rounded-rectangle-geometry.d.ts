import WinUICompositionGeometry = require('./composition-geometry')

/** A rounded rectangle, as a `CompositionRoundedRectangleGeometry`. */
interface WinUICompositionRoundedRectangleGeometry extends WinUICompositionGeometry {
  get size(): { x: number; y: number }
  set size(size: { x?: number; y?: number })

  get cornerRadius(): { x: number; y: number }
  set cornerRadius(radius: { x?: number; y?: number })

  get offset(): { x: number; y: number }
  set offset(offset: { x?: number; y?: number })
}

declare class WinUICompositionRoundedRectangleGeometry {
  protected constructor()
}

export = WinUICompositionRoundedRectangleGeometry
