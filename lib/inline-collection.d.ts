import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIObject = require('./object')

/** The runs of text in a text block, as an `InlineCollection`. */
interface WinUIInlineCollection extends WinUIObject {
  readonly size: number

  /** Add a run of text, such as a `WinUIRun`. */
  append(item: Wrapper): this

  clear(): this
}

declare class WinUIInlineCollection {
  protected constructor()
}

export = WinUIInlineCollection
