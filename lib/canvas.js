const binding = require('../binding')
const { adopt, expose } = require('./handle')
const Panel = require('./panel')

module.exports = exports = class WinUICanvas extends Panel {
  _init() {
    return binding.canvasInit()
  }

  static setZIndex(element, index) {
    binding.canvasSetZIndex(adopt(element), index)
  }

  static getLeft(element) {
    return binding.canvasGetLeft(adopt(element))
  }

  static setLeft(element, length) {
    binding.canvasSetLeft(adopt(element), length)
  }

  static getTop(element) {
    return binding.canvasGetTop(adopt(element))
  }

  static setTop(element, length) {
    binding.canvasSetTop(adopt(element), length)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICanvas }
    }
  }
}

expose(exports)
