const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUIAppWindow extends WinUIObject {
  get id() {
    return binding.appWindowId(this._tag)
  }

  get size() {
    return binding.appWindowSize(this._tag)
  }

  get position() {
    return binding.appWindowPosition(this._tag)
  }
}
