const binding = require('../binding')
const wrap = require('./wrap')
const WinUIObject = require('./object')

module.exports = exports = class WinUIApplication extends WinUIObject {
  static DISPATCHER_SHUTDOWN_MODE = {
    ON_LAST_WINDOW_CLOSE: binding.APPLICATION_DISPATCHER_SHUTDOWN_MODE_ON_LAST_WINDOW_CLOSE,
    ON_EXPLICIT_SHUTDOWN: binding.APPLICATION_DISPATCHER_SHUTDOWN_MODE_ON_EXPLICIT_SHUTDOWN
  }

  static get current() {
    return wrap(WinUIApplication, binding.applicationCurrent())
  }

  get dispatcherShutdownMode() {
    return binding.applicationDispatcherShutdownMode(this._tag)
  }

  set dispatcherShutdownMode(value) {
    binding.applicationDispatcherShutdownMode(this._tag, value)
  }
}
