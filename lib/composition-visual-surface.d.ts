import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUICompositionObject = require('./composition-object')
import WinUIVisual = require('./visual')

/** A surface that shows a visual, as a `CompositionVisualSurface`. */
interface WinUICompositionVisualSurface extends WinUICompositionObject {
  get sourceVisual(): WinUIVisual | null
  set sourceVisual(visual: Wrapper | null)

  get sourceSize(): { x: number; y: number }
  set sourceSize(size: { x?: number; y?: number })

  get sourceOffset(): { x: number; y: number }
  set sourceOffset(offset: { x?: number; y?: number })
}

declare class WinUICompositionVisualSurface {
  protected constructor()
}

export = WinUICompositionVisualSurface
