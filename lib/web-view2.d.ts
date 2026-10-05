import WinUICoreWebView2Settings = require('./core-web-view2-settings')
import WinUIFrameworkElement = require('./framework-element')

/** An element that shows web content with WebView2, as a `WebView2`. */
interface WinUIWebView2 extends WinUIFrameworkElement {
  /** The settings of the web view, or `null` until `ready()` resolves. */
  readonly settings: WinUICoreWebView2Settings | null

  /** The current address, or `null`. Setting it navigates. */
  source: string | null

  /** Resolve once the web view is ready. */
  ready(): Promise<void>

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
