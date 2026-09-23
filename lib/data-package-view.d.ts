import WinUIObject = require('./object')

/** Data read from the clipboard, as a `DataPackageView`. */
interface WinUIDataPackageView extends WinUIObject {
  /** Whether the data has `format`, a `STANDARD_DATA_FORMATS` constant. */
  contains(format: string): boolean

  /** Read the text. `callback` is called with an error message, or with `null` and the text. */
  getTextAsync(callback: (error: string | null, text: string | null) => void): void
}

declare class WinUIDataPackageView {
  protected constructor()

  static readonly STANDARD_DATA_FORMATS: {
    readonly TEXT: string
    readonly HTML: string
    readonly RTF: string
    readonly BITMAP: string
    readonly WEB_LINK: string
    readonly APPLICATION_LINK: string
    readonly STORAGE_ITEMS: string
  }
}

export = WinUIDataPackageView
