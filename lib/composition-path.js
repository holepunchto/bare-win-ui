const binding = require('../binding')
const { adopt } = require('./handle')
const WinUIObject = require('./object')

module.exports = exports = class WinUICompositionPath extends WinUIObject {
  constructor(geometry) {
    super({ tag: binding.compositionPathInit(adopt(geometry)) })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionPath }
    }
  }
}
