import WinUIObject = require('./object')

/** Data to put on the clipboard, as a `DataPackage`. */
interface WinUIDataPackage extends WinUIObject {
  setText(text: string): this

  /** `OPERATION` flags combined with `|`. */
  requestedOperation: number

  getView(): import('./data-package-view') | null
}

declare class WinUIDataPackage {
  constructor()

  static readonly OPERATION: {
    readonly NONE: number
    readonly COPY: number
    readonly MOVE: number
    readonly LINK: number
  }
}

export = WinUIDataPackage
