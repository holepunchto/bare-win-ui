import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIObject = require('./object')
import WinUICompositionColorBrush = require('./composition-color-brush')
import WinUICompositionGeometricClip = require('./composition-geometric-clip')
import WinUICompositionPathGeometry = require('./composition-path-geometry')
import WinUICompositionRoundedRectangleGeometry = require('./composition-rounded-rectangle-geometry')
import WinUICompositionSpriteShape = require('./composition-sprite-shape')
import WinUICompositionSurfaceBrush = require('./composition-surface-brush')
import WinUICompositionVisualSurface = require('./composition-visual-surface')
import WinUIDropShadow = require('./drop-shadow')
import WinUIShapeVisual = require('./shape-visual')
import WinUISpriteVisual = require('./sprite-visual')

/** Makes composition objects, as a `Compositor`. Get one from the `compositor` of any composition object. */
interface WinUICompositor extends WinUIObject {
  createShapeVisual(): WinUIShapeVisual

  createSpriteShape(geometry?: Wrapper): WinUICompositionSpriteShape

  createPathGeometry(path?: Wrapper): WinUICompositionPathGeometry

  createRoundedRectangleGeometry(): WinUICompositionRoundedRectangleGeometry

  /** A colour brush. A component that is left out is 0, except `a`, which is 255. */
  createColorBrush(
    color?: Partial<{ a: number; r: number; g: number; b: number }>
  ): WinUICompositionColorBrush

  createSpriteVisual(): WinUISpriteVisual

  createDropShadow(): WinUIDropShadow

  createVisualSurface(): WinUICompositionVisualSurface

  createSurfaceBrush(surface?: Wrapper): WinUICompositionSurfaceBrush

  createGeometricClip(geometry?: Wrapper): WinUICompositionGeometricClip
}

declare class WinUICompositor {
  protected constructor()
}

export = WinUICompositor
