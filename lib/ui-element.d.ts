import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIDependencyObject = require('./dependency-object')
import WinUIGeneralTransform = require('./general-transform')
import WinUIInputCursor = require('./input-cursor')
import WinUIXamlRoot = require('./xaml-root')

/** The base of everything drawn in XAML, as a `UIElement`. */
interface WinUIUIElement<
  M extends Record<keyof M, unknown[]> = WinUIUIElement.Events
> extends WinUIDependencyObject<M> {
  /** The transform from this element to the coordinates of `target`. */
  transformToVisual(target: WinUIUIElement<any>): WinUIGeneralTransform

  /** What the element is drawn into, or `null` before it is loaded. */
  readonly xamlRoot: WinUIXamlRoot | null

  /** Whether the element can be the target of pointer events. */
  isHitTestVisible: boolean

  /** The cursor shown over the element, or `null` for the default. */
  get protectedCursor(): WinUIInputCursor | null
  set protectedCursor(cursor: Wrapper | null)

  /** How opaque the element is, from 0 to 1. */
  opacity: number

  /** Stop sending the rest of any gestures to this element. */
  releasePointerCaptures(): this

  /** Ask how big the element wants to be within `size`. Read the answer from `desiredSize`. */
  measure(size: { width: number; height: number }): this

  /** Lay out the element and its descendants now, rather than on the next layout pass. */
  updateLayout(): this

  readonly desiredSize: { width: number; height: number }
}

declare class WinUIUIElement<M extends Record<keyof M, unknown[]> = WinUIUIElement.Events> {
  protected constructor()
}

declare namespace WinUIUIElement {
  /**
   * A pointer event. Set `handled` to stop it reaching the parent, and set `capturePointer` on a
   * press to keep getting the gesture after the pointer leaves the element.
   */
  export interface PointerEvent {
    x: number
    y: number
    pointerId: number

    /** A `POINTER_DEVICE_TYPE_*` constant. */
    deviceType: number

    /** Whether the pointer is pressed. A move fires for a pointer that is only over the element. */
    isInContact: boolean

    handled: boolean
    capturePointer: boolean
  }

  export interface Events {
    pointerPressed: [event: PointerEvent]
    pointerReleased: [event: PointerEvent]
    pointerMoved: [event: PointerEvent]
    pointerCanceled: [event: PointerEvent]
  }
}

export = WinUIUIElement
