import WinUIObject = require('./object')

/** The settings of a web view, as `CoreWebView2Settings`. */
interface WinUICoreWebView2Settings extends WinUIObject {
  /** Whether the dev tools can be opened. Defaults to `true`. */
  areDevToolsEnabled: boolean
}

declare class WinUICoreWebView2Settings {
  protected constructor()
}

export = WinUICoreWebView2Settings
