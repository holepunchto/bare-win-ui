const binding = require('../binding')
const wrap = require('./wrap')
const WinUIObject = require('./object')

module.exports = exports = class WinUIGeneralTransform extends WinUIObject {
  transformPoint(x, y) {
    return binding.generalTransformTransformPoint(this._tag, x, y)
  }

  transformBounds(x, y, width, height) {
    return binding.generalTransformTransformBounds(this._tag, x, y, width, height)
  }

  get inverse() {
    return wrap(WinUIGeneralTransform, binding.generalTransformInverse(this._tag))
  }
}
