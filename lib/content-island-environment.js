const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUIContentIslandEnvironment extends WinUIObject {
  get appWindowId() {
    return binding.contentIslandEnvironmentAppWindowId(this._tag)
  }
}
