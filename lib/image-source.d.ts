import WinUIDependencyObject = require('./dependency-object')

/** Anything an image can show, as an `ImageSource`. */
interface WinUIImageSource extends WinUIDependencyObject {}

declare class WinUIImageSource {
  protected constructor()
}

export = WinUIImageSource
