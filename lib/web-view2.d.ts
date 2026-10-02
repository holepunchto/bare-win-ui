import WinUIFrameworkElement = require('./framework-element')

/** An element that shows web content with WebView2, as a `WebView2`. */
interface WinUIWebView2 extends WinUIFrameworkElement {
  /** The current address, or `null`. Setting it navigates. */
  source: string | null

  /** Load `uri`, once the web view is ready. */
  navigate(uri: string): Promise<void>

  /** Load `html` as the page, once the web view is ready. */
  navigateToString(html: string): Promise<void>

  openDevToolsWindow(): Promise<void>
}

declare class WinUIWebView2 {
  constructor()
}

export = WinUIWebView2
