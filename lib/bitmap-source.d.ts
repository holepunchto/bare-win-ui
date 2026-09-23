import WinUIImageSource = require('./image-source')

/** A bitmap, as a `BitmapSource`. */
interface WinUIBitmapSource extends WinUIImageSource {
  readonly pixelWidth: number

  readonly pixelHeight: number
}

declare class WinUIBitmapSource {
  protected constructor()
}

export = WinUIBitmapSource
