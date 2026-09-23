import WinUIInputCursor = require('./input-cursor')

/** A system cursor, as an `InputSystemCursor`. */
interface WinUIInputSystemCursor extends WinUIInputCursor {
  readonly cursorShape: number
}

declare class WinUIInputSystemCursor {
  protected constructor()

  /** A system cursor, as a `SHAPE` constant. */
  static create(shape: number): WinUIInputSystemCursor

  static readonly SHAPE: {
    readonly ARROW: number
    readonly CROSS: number
    readonly HAND: number
    readonly HELP: number
    readonly IBEAM: number
    readonly SIZE_ALL: number
    readonly SIZE_NORTHEAST_SOUTHWEST: number
    readonly SIZE_NORTH_SOUTH: number
    readonly SIZE_NORTHWEST_SOUTHEAST: number
    readonly SIZE_WEST_EAST: number
    readonly UNIVERSAL_NO: number
    readonly UP_ARROW: number
    readonly WAIT: number
    readonly PIN: number
    readonly PERSON: number
    readonly APP_STARTING: number
  }
}

export = WinUIInputSystemCursor
