import WinUIObject = require('./object')

/** An object with XAML properties, as a `DependencyObject`. */
interface WinUIDependencyObject<M extends Record<keyof M, unknown[]> = {}> extends WinUIObject<M> {}

declare class WinUIDependencyObject<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = WinUIDependencyObject
