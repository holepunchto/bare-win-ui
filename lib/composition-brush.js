const { expose } = require('./handle')
const CompositionObject = require('./composition-object')

module.exports = exports = class WinUICompositionBrush extends CompositionObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionBrush }
    }
  }
}

expose(exports)
