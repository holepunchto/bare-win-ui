import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUICompositionGeometry = require('./composition-geometry')

/** A geometry made from a path, as a `CompositionPathGeometry`. */
interface WinUICompositionPathGeometry extends WinUICompositionGeometry {
  /** The path to draw, such as a `WinUICompositionPath`. */
  set path(path: Wrapper)
}

declare class WinUICompositionPathGeometry {
  protected constructor()
}

export = WinUICompositionPathGeometry
