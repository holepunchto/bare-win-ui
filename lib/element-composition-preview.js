const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const Visual = require('./visual')

module.exports = exports = class WinUIElementCompositionPreview {
  static getElementVisual(element) {
    return wrap(Visual, binding.elementCompositionPreviewGetElementVisual(adopt(element)))
  }

  static getElementChildVisual(element) {
    return wrap(Visual, binding.elementCompositionPreviewGetElementChildVisual(adopt(element)))
  }

  static setElementChildVisual(element, visual) {
    binding.elementCompositionPreviewSetElementChildVisual(adopt(element), adopt(visual))
  }
}
