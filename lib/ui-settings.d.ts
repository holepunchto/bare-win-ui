import WinUIObject = require('./object')

/** What the user has set in Windows, as `UISettings`. */
interface WinUIUISettings extends WinUIObject {
  /** How much larger the user wants text to be. */
  readonly textScaleFactor: number
}

declare class WinUIUISettings {
  constructor()
}

export = WinUIUISettings
