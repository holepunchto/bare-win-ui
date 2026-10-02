const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUIUISettings extends WinUIObject {
  _init() {
    return binding.uiSettingsInit()
  }

  get textScaleFactor() {
    return binding.uiSettingsTextScaleFactor(this._tag)
  }
}
