import WinUIObject = require('./object')

/** A display, in physical pixels, as a `DisplayArea`. */
interface WinUIDisplayArea extends WinUIObject {
  readonly outerBounds: { x: number; y: number; width: number; height: number }

  /** The bounds without the taskbar. */
  readonly workArea: { x: number; y: number; width: number; height: number }

  readonly isPrimary: boolean
}

declare class WinUIDisplayArea {
  protected constructor()

  static readonly primary: WinUIDisplayArea | null

  /** The display a window is on. `fallback` is a `FALLBACK` constant and defaults to `NEAREST`. */
  static getFromWindowId(id: number, fallback?: number): WinUIDisplayArea | null

  static readonly FALLBACK: {
    readonly NONE: number
    readonly PRIMARY: number
    readonly NEAREST: number
  }
}

export = WinUIDisplayArea
