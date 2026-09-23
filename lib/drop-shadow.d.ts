import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUICompositionShadow = require('./composition-shadow')
import WinUICompositionBrush = require('./composition-brush')

/** A drop shadow, as a `DropShadow`. */
interface WinUIDropShadow extends WinUICompositionShadow {
  get color(): { a: number; r: number; g: number; b: number }
  set color(color: Partial<{ a: number; r: number; g: number; b: number }>)

  get offset(): { x: number; y: number; z: number }
  set offset(offset: { x?: number; y?: number; z?: number })

  blurRadius: number

  /** How opaque the shadow is, from 0 to 1. */
  opacity: number

  /** A brush whose opaque parts decide the shape of the shadow, or `null`. */
  get mask(): WinUICompositionBrush | null
  set mask(mask: Wrapper | null)
}

declare class WinUIDropShadow {
  protected constructor()
}

export = WinUIDropShadow
