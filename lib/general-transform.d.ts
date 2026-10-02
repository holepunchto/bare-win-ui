import WinUIObject = require('./object')

/** A transform between the coordinates of two elements, as a `GeneralTransform`. */
interface WinUIGeneralTransform extends WinUIObject {
  transformPoint(x: number, y: number): { x: number; y: number }

  transformBounds(
    x: number,
    y: number,
    width: number,
    height: number
  ): { x: number; y: number; width: number; height: number }

  readonly inverse: WinUIGeneralTransform | null
}

declare class WinUIGeneralTransform {
  protected constructor()
}

export = WinUIGeneralTransform
