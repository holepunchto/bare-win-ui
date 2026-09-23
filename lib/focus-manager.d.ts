import WinUIUIElement = require('./ui-element')

/**
 * Move the focus from `element` in `direction`, a `FOCUS_NAVIGATION_DIRECTION` constant. Focus
 * cannot be cleared, so this is how to let go of it. Returns whether it moved.
 */
export function tryMoveFocus(element: WinUIUIElement<any>, direction: number): boolean

export const FOCUS_NAVIGATION_DIRECTION: {
  readonly NEXT: number
  readonly PREVIOUS: number
  readonly UP: number
  readonly DOWN: number
  readonly LEFT: number
  readonly RIGHT: number
  readonly NONE: number
}
