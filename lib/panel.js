const binding = require('../binding')
const { adopt } = require('./handle')
const retain = require('./retain')
const wrap = require('./wrap')
const Brush = require('./brush')
const UIElementCollection = require('./ui-element-collection')
const FrameworkElement = require('./framework-element')

module.exports = exports = class WinUIPanel extends FrameworkElement {
  get children() {
    return retain(this, '_children', UIElementCollection, binding.panelChildren(this._tag))
  }

  get background() {
    return wrap(Brush, binding.panelBackground(this._tag))
  }

  set background(value) {
    binding.panelBackground(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIPanel }
    }
  }
}
