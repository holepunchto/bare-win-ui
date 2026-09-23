import WinUIBrush = require('./brush')

/** A brush that paints one colour, as a `SolidColorBrush`. A component that is left out is 0, except `a`, which is 255. */
interface WinUISolidColorBrush extends WinUIBrush {
  get color(): { a: number; r: number; g: number; b: number }
  set color(color: Partial<{ a: number; r: number; g: number; b: number }>)
}

declare class WinUISolidColorBrush {
  constructor(opts?: { color?: Partial<{ a: number; r: number; g: number; b: number }> | null })
}

export = WinUISolidColorBrush
