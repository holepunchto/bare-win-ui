import WinUIControl = require('./control')

/** A box for entering a password, as a `PasswordBox`. It has no selection and does not report pointer events. */
interface WinUIPasswordBox extends WinUIControl<WinUIPasswordBox.Events> {
  /** Whether the user can show the password, as a `PASSWORD_REVEAL_MODE` constant. */
  set passwordRevealMode(value: number)

  password: string

  /** Text shown while the box is empty. */
  placeholderText: string
}

declare class WinUIPasswordBox {
  constructor()

  static readonly PASSWORD_REVEAL_MODE: {
    readonly PEEK: number
    readonly HIDDEN: number
    readonly VISIBLE: number
  }
}

declare namespace WinUIPasswordBox {
  export interface Events {
    passwordChanged: []
    gotFocus: []
    lostFocus: []
    loaded: []
  }
}

export = WinUIPasswordBox
