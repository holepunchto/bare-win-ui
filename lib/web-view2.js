const binding = require('../binding')
const retain = require('./retain')
const CoreWebView2Settings = require('./core-web-view2-settings')
const FrameworkElement = require('./framework-element')

module.exports = exports = class WinUIWebView2 extends FrameworkElement {
  _init() {
    this._ready = Promise.withResolvers()

    return binding.webView2Init(this, this._onready)
  }

  get source() {
    return binding.webView2Source(this._tag)
  }

  set source(value) {
    binding.webView2Source(this._tag, value)
  }

  get settings() {
    return retain(this, '_settings', CoreWebView2Settings, binding.webView2Settings(this._tag))
  }

  ready() {
    return this._ready.promise
  }

  async navigate(uri) {
    await this._ready.promise

    binding.webView2Navigate(this._tag, uri)
  }

  async navigateToString(html) {
    await this._ready.promise

    binding.webView2NavigateToString(this._tag, html)
  }

  async openDevToolsWindow() {
    await this._ready.promise

    binding.webView2OpenDevToolsWindow(this._tag)
  }

  _onready(err) {
    if (err) this._ready.reject(new Error(err))
    else this._ready.resolve()
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIWebView2 },

      source: this.source
    }
  }
}
