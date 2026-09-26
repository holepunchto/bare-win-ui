const binding = require('../binding')
const { expose } = require('./handle')
const WinUIObject = require('./object')

module.exports = exports = class WinUIFontFamily extends WinUIObject {
  _init(opts) {
    const { familyName } = opts

    return binding.fontFamilyInit(familyName)
  }

  get source() {
    return binding.fontFamilySource(this._tag)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIFontFamily }
    }
  }
}

expose(exports)
