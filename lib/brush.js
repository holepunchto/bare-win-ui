const DependencyObject = require('./dependency-object')

module.exports = exports = class WinUIBrush extends DependencyObject {
  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIBrush }
    }
  }
}
