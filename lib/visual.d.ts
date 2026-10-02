import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUICompositionObject = require('./composition-object')
import WinUICompositionClip = require('./composition-clip')

/** Something the compositor draws, as a `Visual`. */
interface WinUIVisual extends WinUICompositionObject {
  get size(): { x: number; y: number }
  set size(size: { x?: number; y?: number })

  get clip(): WinUICompositionClip | null
  set clip(clip: Wrapper | null)

  /** The transform, as sixteen numbers in the order CSS uses for `matrix3d()`. */
  transformMatrix: number[]
}

declare class WinUIVisual {
  protected constructor()
}

export = WinUIVisual
