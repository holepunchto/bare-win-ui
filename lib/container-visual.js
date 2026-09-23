const Visual = require('./visual')

module.exports = exports = class WinUIContainerVisual extends Visual {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIContainerVisual }
    }
  }
}
