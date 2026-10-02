import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIObject = require('./object')
import WinUIUIElement = require('./ui-element')

/** The children of a panel, as a `UIElementCollection`. */
interface WinUIUIElementCollection extends WinUIObject {
  readonly size: number

  getAt(index: number): WinUIUIElement | null

  /** The index of `value`, or -1. */
  indexOf(value: Wrapper): number

  append(value: Wrapper): this

  insertAt(index: number, value: Wrapper): this

  removeAt(index: number): this

  clear(): this
}

declare class WinUIUIElementCollection {
  protected constructor()
}

export = WinUIUIElementCollection
