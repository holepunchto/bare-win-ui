import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIFrameworkElement = require('./framework-element')
import WinUIImageSource = require('./image-source')

/** An element that shows an image, as an `Image`. It does not report pointer events. */
interface WinUIImage extends WinUIFrameworkElement<WinUIImage.Events> {
  /** What the image shows. Decoding happens later, and reports through the events. */
  get source(): WinUIImageSource | null
  set source(source: Wrapper | null)

  /** How the image is fitted to the element, as a `STRETCH` constant. */
  stretch: number
}

declare class WinUIImage {
  constructor()

  static readonly STRETCH: {
    readonly NONE: number
    readonly FILL: number
    readonly UNIFORM: number
    readonly UNIFORM_TO_FILL: number
  }
}

declare namespace WinUIImage {
  export interface Events {
    imageOpened: []
    imageFailed: [event: { errorMessage: string }]
  }
}

export = WinUIImage
