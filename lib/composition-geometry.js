const { expose } = require('./handle')
const CompositionObject = require('./composition-object')

module.exports = exports = class WinUICompositionGeometry extends CompositionObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionGeometry }
    }
  }
}

expose(exports)
