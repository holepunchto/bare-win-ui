import WinUIDependencyObject = require('./dependency-object')

/** Something to paint with, as a `Brush`. */
interface WinUIBrush extends WinUIDependencyObject {}

declare class WinUIBrush {
  protected constructor()
}

export = WinUIBrush
