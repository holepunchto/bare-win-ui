import WinUIObject = require('./object')

/** Where content is hosted, as a `ContentIslandEnvironment`. */
interface WinUIContentIslandEnvironment extends WinUIObject {
  /** The `WindowId` of the window the content is in. */
  readonly appWindowId: bigint
}

declare class WinUIContentIslandEnvironment {
  protected constructor()
}

export = WinUIContentIslandEnvironment
