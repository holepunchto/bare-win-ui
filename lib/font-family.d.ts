import WinUIObject = require('./object')

/** A font family, as a `FontFamily`. */
interface WinUIFontFamily extends WinUIObject {
  /** The name of the family. */
  readonly source: string
}

declare class WinUIFontFamily {
  constructor(opts: { familyName: string })
}

export = WinUIFontFamily
