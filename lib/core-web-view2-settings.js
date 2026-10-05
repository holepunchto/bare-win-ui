const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUICoreWebView2Settings extends WinUIObject {
  get areDevToolsEnabled() {
    return binding.coreWebView2SettingsAreDevToolsEnabled(this._tag)
  }

  set areDevToolsEnabled(value) {
    binding.coreWebView2SettingsAreDevToolsEnabled(this._tag, value)
  }
}
