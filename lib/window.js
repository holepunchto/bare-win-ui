const EventEmitter = require('bare-events')
const binding = require('../binding')

module.exports = exports = class WinUIWindow extends EventEmitter {
  constructor() {
    super()

    this._handle = binding.windowInit(this)
  }

  activate() {
    binding.windowActivate(this._handle)
    return this
  }

  close() {
    binding.windowClose(this._handle)
    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIWindow }
    }
  }
}
