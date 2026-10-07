import WinUIImageSource = require('./image-source')

/** A bitmap, as a `BitmapSource`. */
interface WinUIBitmapSource<M extends Record<keyof M, unknown[]> = {}> extends WinUIImageSource<M> {
  readonly pixelWidth: number
  readonly pixelHeight: number
}

declare class WinUIBitmapSource<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = WinUIBitmapSource
