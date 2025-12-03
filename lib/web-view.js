const binding = require('../binding')
const WinUIElement = require('./element')

module.exports = exports = class WinUIWebView extends WinUIElement {
  constructor() {
    super()

    this._ready = Promise.withResolvers()

    this._handle = binding.webViewInit(this, this._onready)

    binding.webViewEnsureReady(this._handle)
  }

  get width() {
    return binding.webViewWidth(this._handle)
  }

  set width(value) {
    binding.webViewWidth(this._handle, value)
  }

  get height() {
    return binding.webViewHeight(this._handle)
  }

  set height(value) {
    binding.webViewHeight(this._handle, value)
  }

  get source() {
    return binding.webViewSource(this._handle)
  }

  set source(value) {
    binding.webViewSource(this._handle, value)
  }

  async navigate(url) {
    await this._ready.promise

    binding.webViewNavigate(this._handle, url)
  }

  async navigateToString(html) {
    await this._ready.promise

    binding.webViewNavigateToString(this._handle, html)
  }

  async openDevToolsWindow() {
    await this._ready.promise

    binding.webViewOpenDevToolsWindow(this._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIWebView },

      width: this.width,
      height: this.height,
      source: this.source
    }
  }

  _onready() {
    this._ready.resolve()
  }
}
