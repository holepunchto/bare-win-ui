import WinUIDependencyObject = require('./dependency-object')

/** Anything an image can show, as an `ImageSource`. */
interface WinUIImageSource<
  M extends Record<keyof M, unknown[]> = {}
> extends WinUIDependencyObject<M> {}

declare class WinUIImageSource<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = WinUIImageSource
