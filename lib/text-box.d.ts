import WinUIControl = require('./control')

/** A box for editing text, as a `TextBox`. It does not report pointer events. */
interface WinUITextBox extends WinUIControl<WinUITextBox.Events> {
  text: string

  /** Text shown while the box is empty. */
  placeholderText: string

  isReadOnly: boolean

  /** Whether the box takes several lines. */
  acceptsReturn: boolean

  isSpellCheckEnabled: boolean

  selectionStart: number

  selectionLength: number

  /** A `TEXT_WRAPPING` constant. */
  textWrapping: number

  /** What the touch keyboard offers, as an `INPUT_SCOPE_NAME_VALUE` constant. */
  set inputScope(value: number)

  /** A `TEXT_ALIGNMENT` constant. */
  textAlignment: number
}

declare class WinUITextBox {
  constructor()

  static readonly TEXT_WRAPPING: {
    readonly NO_WRAP: number
    readonly WRAP: number
    readonly WRAP_WHOLE_WORDS: number
  }

  static readonly INPUT_SCOPE_NAME_VALUE: {
    readonly DEFAULT: number
    readonly URL: number
    readonly EMAIL_SMTP_ADDRESS: number
    readonly NUMBER: number
    readonly TELEPHONE_NUMBER: number
    readonly DIGITS: number
    readonly CURRENCY_AMOUNT: number
  }

  static readonly TEXT_ALIGNMENT: {
    readonly CENTER: number
    readonly LEFT: number
    readonly START: number
    readonly RIGHT: number
    readonly END: number
    readonly JUSTIFY: number
  }
}

declare namespace WinUITextBox {
  export interface Events {
    /** The text is changing, before it is drawn. */
    textChanging: []
    textChanged: []
    selectionChanged: []
    gotFocus: []
    lostFocus: []

    /** A key was pressed. `key` is a `VirtualKey` number. */
    keyDown: [event: { key: number }]
    loaded: []
  }
}

export = WinUITextBox
