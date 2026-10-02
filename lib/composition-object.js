const binding = require('../binding')
const wrap = require('./wrap')
const WinUIObject = require('./object')

module.exports = exports = class WinUICompositionObject extends WinUIObject {
  get compositor() {
    return wrap(require('./compositor'), binding.compositionObjectCompositor(this._tag))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionObject }
    }
  }
}
