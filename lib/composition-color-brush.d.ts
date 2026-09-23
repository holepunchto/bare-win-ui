import WinUICompositionBrush = require('./composition-brush')

/** A brush that paints one colour, as a `CompositionColorBrush`. */
interface WinUICompositionColorBrush extends WinUICompositionBrush {
  get color(): { a: number; r: number; g: number; b: number }
  set color(color: Partial<{ a: number; r: number; g: number; b: number }>)
}

declare class WinUICompositionColorBrush {
  protected constructor()
}

export = WinUICompositionColorBrush
