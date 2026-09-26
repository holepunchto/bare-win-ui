const { expose } = require('./handle')
const CompositionObject = require('./composition-object')

module.exports = exports = class WinUICompositionShadow extends CompositionObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionShadow }
    }
  }
}

expose(exports)
