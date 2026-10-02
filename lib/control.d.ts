import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIFrameworkElement = require('./framework-element')
import WinUIBrush = require('./brush')

/** The base of the interactive controls, as a `Control`. */
interface WinUIControl<
  M extends Record<keyof M, unknown[]> = WinUIFrameworkElement.Events
> extends WinUIFrameworkElement<M> {
  isEnabled: boolean

  get background(): WinUIBrush | null
  set background(brush: Wrapper | null)

  get borderBrush(): WinUIBrush | null
  set borderBrush(brush: Wrapper | null)

  /** Whether WinUI draws its focus rectangle when the control has focus. */
  useSystemFocusVisuals: boolean

  /** The brush the content is drawn with, such as the text. */
  get foreground(): WinUIBrush | null
  set foreground(brush: Wrapper | null)

  set borderThickness(value: number)

  /** The space inside the control, as one number for every side or one per side. */
  set padding(value: number | { left?: number; top?: number; right?: number; bottom?: number })

  /** A `HORIZONTAL_ALIGNMENT` constant from `WinUIFrameworkElement`. */
  horizontalContentAlignment: number

  /** A `VERTICAL_ALIGNMENT` constant from `WinUIFrameworkElement`. */
  verticalContentAlignment: number

  set cornerRadius(value: number)

  /** The part of the control template called `name`, or `null`. */
  templateChild(name: string): WinUIFrameworkElement | null

  /** Move the focus to the control. Returns whether it took it. */
  focus(state?: number): boolean
}

declare class WinUIControl<M extends Record<keyof M, unknown[]> = WinUIFrameworkElement.Events> {
  protected constructor()

  static readonly FOCUS_STATE: {
    readonly UNFOCUSED: number
    readonly POINTER: number
    readonly KEYBOARD: number
    readonly PROGRAMMATIC: number
  }
}

export = WinUIControl
