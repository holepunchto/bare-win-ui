const { expose } = require('./handle')
const CompositionBrush = require('./composition-brush')

module.exports = exports = class WinUICompositionSurfaceBrush extends CompositionBrush {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionSurfaceBrush }
    }
  }
}

expose(exports)
