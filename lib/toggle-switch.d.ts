import WinUIControl = require('./control')

/** An on and off switch, as a `ToggleSwitch`. It does not report pointer events. */
interface WinUIToggleSwitch extends WinUIControl<WinUIToggleSwitch.Events> {
  isOn: boolean

  /** Replace the "On" and "Off" labels shown beside the switch. */
  content(on: string, off: string): this
}

declare class WinUIToggleSwitch {
  constructor()
}

declare namespace WinUIToggleSwitch {
  export interface Events {
    /** `isOn` changed, whether the user or the program changed it. */
    toggled: []
    loaded: []
  }
}

export = WinUIToggleSwitch
