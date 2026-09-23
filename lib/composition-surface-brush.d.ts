import WinUICompositionBrush = require('./composition-brush')

/** A brush that paints a surface, as a `CompositionSurfaceBrush`. */
interface WinUICompositionSurfaceBrush extends WinUICompositionBrush {}

declare class WinUICompositionSurfaceBrush {
  protected constructor()
}

export = WinUICompositionSurfaceBrush
