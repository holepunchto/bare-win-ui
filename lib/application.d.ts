import WinUIObject = require('./object')

/** The app, as an `Application`. */
interface WinUIApplication extends WinUIObject {
  /**
   * A `DISPATCHER_SHUTDOWN_MODE` constant. By default the app shuts down once its last window has
   * closed.
   */
  dispatcherShutdownMode: number
}

declare class WinUIApplication {
  protected constructor()

  /** The app the runtime started. */
  static readonly current: WinUIApplication | null

  static readonly DISPATCHER_SHUTDOWN_MODE: {
    readonly ON_LAST_WINDOW_CLOSE: number
    readonly ON_EXPLICIT_SHUTDOWN: number
  }
}

export = WinUIApplication
