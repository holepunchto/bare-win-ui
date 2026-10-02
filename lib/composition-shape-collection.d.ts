import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIObject = require('./object')
import WinUICompositionShape = require('./composition-shape')

/** The shapes of a shape visual, as a `CompositionShapeCollection`. */
interface WinUICompositionShapeCollection extends WinUIObject {
  readonly size: number

  getAt(index: number): WinUICompositionShape | null

  /** The index of `value`, or -1. */
  indexOf(value: Wrapper): number

  append(value: Wrapper): this

  insertAt(index: number, value: Wrapper): this

  removeAt(index: number): this

  clear(): this
}

declare class WinUICompositionShapeCollection {
  protected constructor()
}

export = WinUICompositionShapeCollection
