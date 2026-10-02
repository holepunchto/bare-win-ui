import WinUIBitmapSource = require('./bitmap-source')

/** A bitmap loaded from an address, as a `BitmapImage`. */
interface WinUIBitmapImage extends WinUIBitmapSource {
  /** The address of the image, such as a file URI. */
  uriSource: string | null
}

declare class WinUIBitmapImage {
  constructor()
}

export = WinUIBitmapImage
