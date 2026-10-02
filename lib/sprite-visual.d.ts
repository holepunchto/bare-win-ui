import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIContainerVisual = require('./container-visual')
import WinUICompositionBrush = require('./composition-brush')
import WinUICompositionShadow = require('./composition-shadow')

/** A visual filled with a brush, as a `SpriteVisual`. */
interface WinUISpriteVisual extends WinUIContainerVisual {
  get brush(): WinUICompositionBrush | null
  set brush(brush: Wrapper | null)

  get shadow(): WinUICompositionShadow | null
  set shadow(shadow: Wrapper | null)
}

declare class WinUISpriteVisual {
  protected constructor()
}

export = WinUISpriteVisual
