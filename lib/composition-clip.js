const { expose } = require('./handle')
const CompositionObject = require('./composition-object')

module.exports = exports = class WinUICompositionClip extends CompositionObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionClip }
    }
  }
}

expose(exports)
