import WinUIObject = require('./object')

/** A window as the system sees it, in physical pixels, as an `AppWindow`. */
interface WinUIAppWindow extends WinUIObject {
  /** The number the system knows the window by. */
  readonly id: bigint

  readonly size: { width: number; height: number }

  readonly position: { x: number; y: number }

  readonly isVisible: boolean

  show(activateWindow?: boolean): this

  hide(): this
}

declare class WinUIAppWindow {
  protected constructor()
}

export = WinUIAppWindow
