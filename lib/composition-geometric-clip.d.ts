import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUICompositionClip = require('./composition-clip')
import WinUICompositionGeometry = require('./composition-geometry')

/** A clip to a geometry, as a `CompositionGeometricClip`. */
interface WinUICompositionGeometricClip extends WinUICompositionClip {
  get geometry(): WinUICompositionGeometry | null
  set geometry(geometry: Wrapper | null)
}

declare class WinUICompositionGeometricClip {
  protected constructor()
}

export = WinUICompositionGeometricClip
