import WinUIObject = require('./object')

/** The base of the composition objects, which draw below XAML, as a `CompositionObject`. */
interface WinUICompositionObject extends WinUIObject {
  readonly compositor: import('./compositor') | null
}

declare class WinUICompositionObject {
  protected constructor()
}

export = WinUICompositionObject
