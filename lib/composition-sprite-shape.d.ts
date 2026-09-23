import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUICompositionShape = require('./composition-shape')
import WinUICompositionBrush = require('./composition-brush')
import WinUICompositionGeometry = require('./composition-geometry')

/** A shape drawn from a geometry, as a `CompositionSpriteShape`. */
interface WinUICompositionSpriteShape extends WinUICompositionShape {
  get geometry(): WinUICompositionGeometry | null
  set geometry(geometry: Wrapper | null)

  get fillBrush(): WinUICompositionBrush | null
  set fillBrush(brush: Wrapper | null)

  get strokeBrush(): WinUICompositionBrush | null
  set strokeBrush(brush: Wrapper | null)

  /** The lengths of the dashes and gaps, in multiples of `strokeThickness`. */
  set strokeDashArray(dashes: number[])

  strokeThickness: number
}

declare class WinUICompositionSpriteShape {
  protected constructor()
}

export = WinUICompositionSpriteShape
