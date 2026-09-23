import WinUIObject = require('./object')

/** What elements are drawn into, as a `XamlRoot`. */
interface WinUIXamlRoot extends WinUIObject {
  readonly size: { width: number; height: number }

  /** How many physical pixels there are per device independent pixel. */
  readonly rasterizationScale: number

  readonly isHostVisible: boolean
}

declare class WinUIXamlRoot {
  protected constructor()
}

export = WinUIXamlRoot
