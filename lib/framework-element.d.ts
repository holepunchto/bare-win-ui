import WinUIDependencyObject = require('./dependency-object')
import WinUIUIElement = require('./ui-element')

/** An element that takes part in layout, as a `FrameworkElement`. */
interface WinUIFrameworkElement<
  M extends Record<keyof M, unknown[]> = WinUIFrameworkElement.Events
> extends WinUIUIElement<M> {
  /** Force light or dark mode for the element, as an `ELEMENT_THEME` constant. */
  requestedTheme: number

  /** Whether the element is drawn in light or dark mode, as an `ELEMENT_THEME` constant. */
  readonly actualTheme: number

  /** The width the element asks for, or `NaN` to size it automatically. */
  width: number

  /** The height the element asks for, or `NaN` to size it automatically. */
  height: number

  /** Override the theme resource `key` with `value`, such as a size the template enforces. */
  resource(key: string, value: number): this

  set minWidth(value: number)

  set minHeight(value: number)

  /** The width the element was given in the last layout. */
  readonly actualWidth: number

  /** The height the element was given in the last layout. */
  readonly actualHeight: number

  /** A `HORIZONTAL_ALIGNMENT` constant. */
  horizontalAlignment: number

  /** A `VERTICAL_ALIGNMENT` constant. */
  verticalAlignment: number

  readonly parent: WinUIDependencyObject | null
}

declare class WinUIFrameworkElement<
  M extends Record<keyof M, unknown[]> = WinUIFrameworkElement.Events
> {
  protected constructor()

  static readonly HORIZONTAL_ALIGNMENT: {
    readonly LEFT: number
    readonly CENTER: number
    readonly RIGHT: number
    readonly STRETCH: number
  }

  static readonly VERTICAL_ALIGNMENT: {
    readonly TOP: number
    readonly CENTER: number
    readonly BOTTOM: number
    readonly STRETCH: number
  }

  static readonly ELEMENT_THEME: {
    readonly DEFAULT: number
    readonly LIGHT: number
    readonly DARK: number
  }
}

declare namespace WinUIFrameworkElement {
  export interface Events {
    pointerPressed: [event: WinUIUIElement.PointerEvent]
    pointerReleased: [event: WinUIUIElement.PointerEvent]
    pointerMoved: [event: WinUIUIElement.PointerEvent]
    pointerCanceled: [event: WinUIUIElement.PointerEvent]

    /** The element switched between light and dark mode. */
    actualThemeChanged: []
  }
}

export = WinUIFrameworkElement
