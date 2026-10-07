import WinUIBitmapSource = require('./bitmap-source')

/**
 * A bitmap loaded from an address, as a `BitmapImage`. It reports its own decode, which an image
 * showing it does too, but an image keeps reporting for a bitmap it no longer shows.
 */
interface WinUIBitmapImage extends WinUIBitmapSource<WinUIBitmapImage.Events> {
  /** The address of the image, such as a file URI. */
  uriSource: string | null
}

declare class WinUIBitmapImage {
  constructor()
}

declare namespace WinUIBitmapImage {
  export interface Events {
    imageOpened: []
    imageFailed: [event: { errorMessage: string }]
  }
}

export = WinUIBitmapImage
