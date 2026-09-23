import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIFrameworkElement = require('./framework-element')
import WinUIBrush = require('./brush')
import WinUIUIElementCollection = require('./ui-element-collection')

/** An element that holds other elements, as a `Panel`. */
interface WinUIPanel<
  M extends Record<keyof M, unknown[]> = WinUIFrameworkElement.Events
> extends WinUIFrameworkElement<M> {
  /** The children of the panel. Add to it to show elements in the panel. */
  readonly children: WinUIUIElementCollection

  get background(): WinUIBrush | null
  set background(brush: Wrapper | null)
}

declare class WinUIPanel<M extends Record<keyof M, unknown[]> = WinUIFrameworkElement.Events> {
  protected constructor()
}

export = WinUIPanel
