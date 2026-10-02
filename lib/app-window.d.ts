import WinUIObject = require('./object')

/** A window as the system sees it, in physical pixels, as an `AppWindow`. */
interface WinUIAppWindow extends WinUIObject {
  /** The number the system knows the window by. */
  readonly id: number

  readonly size: { width: number; height: number }

  readonly position: { x: number; y: number }
}

declare class WinUIAppWindow {
  protected constructor()
}

export = WinUIAppWindow
