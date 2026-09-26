const binding = require('../binding')
const { expose } = require('./handle')
const Control = require('./control')

module.exports = exports = class WinUIProgressRing extends Control {
  _init() {
    return binding.progressRingInit()
  }

  get isActive() {
    return binding.progressRingIsActive(this._tag)
  }

  set isActive(value) {
    binding.progressRingIsActive(this._tag, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIProgressRing }
    }
  }
}

expose(exports)
