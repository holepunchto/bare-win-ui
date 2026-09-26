const { expose } = require('./handle')
const WinUIObject = require('./object')

module.exports = exports = class WinUIDependencyObject extends WinUIObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIDependencyObject }
    }
  }
}

expose(exports)
