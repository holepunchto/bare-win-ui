const { expose } = require('./handle')
const WinUIObject = require('./object')

module.exports = exports = class WinUIInputCursor extends WinUIObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIInputCursor }
    }
  }
}

expose(exports)
