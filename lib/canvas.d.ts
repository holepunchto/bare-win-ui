import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIPanel = require('./panel')

/** A panel that places each child at a position, as a `Canvas`. */
interface WinUICanvas extends WinUIPanel {}

declare class WinUICanvas {
  constructor()

  /** Set which children are drawn on top. Higher is on top. */
  static setZIndex(element: Wrapper, index: number): void

  static getLeft(element: Wrapper): number

  static setLeft(element: Wrapper, length: number): void

  static getTop(element: Wrapper): number

  static setTop(element: Wrapper, length: number): void
}

export = WinUICanvas
