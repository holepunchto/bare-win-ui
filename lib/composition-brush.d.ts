import WinUICompositionObject = require('./composition-object')

/** Something the compositor paints with, as a `CompositionBrush`. */
interface WinUICompositionBrush extends WinUICompositionObject {}

declare class WinUICompositionBrush {
  protected constructor()
}

export = WinUICompositionBrush
