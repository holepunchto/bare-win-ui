import WinUIObject = require('./object')
import WinUIContentIslandEnvironment = require('./content-island-environment')

/** What elements are drawn into, as a `XamlRoot`. */
interface WinUIXamlRoot extends WinUIObject<WinUIXamlRoot.Events> {
  readonly size: { width: number; height: number }

  /** How many physical pixels there are per device independent pixel. */
  readonly rasterizationScale: number

  readonly isHostVisible: boolean

  /** What the content is hosted in, including the window it is in. */
  readonly contentIslandEnvironment: WinUIContentIslandEnvironment | null
}

declare class WinUIXamlRoot {
  protected constructor()
}

declare namespace WinUIXamlRoot {
  export interface Events {
    /** The size, scale or visibility changed, for example because the window moved to another display. */
    changed: []
  }
}

export = WinUIXamlRoot
