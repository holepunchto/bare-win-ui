import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIVisual = require('./visual')

/** Connects XAML elements to composition visuals, as `ElementCompositionPreview`. */
interface WinUIElementCompositionPreview {}

declare class WinUIElementCompositionPreview {
  private constructor()

  /** The visual the element is drawn with. */
  static getElementVisual(element: Wrapper): WinUIVisual | null

  static getElementChildVisual(element: Wrapper): WinUIVisual | null

  /** Draw `visual` on top of the element. */
  static setElementChildVisual(element: Wrapper, visual: Wrapper): void
}

export = WinUIElementCompositionPreview
