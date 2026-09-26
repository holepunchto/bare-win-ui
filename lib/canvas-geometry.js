const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const WinUIObject = require('./object')

module.exports = exports = class WinUICanvasGeometry extends WinUIObject {
  static createPath(builder) {
    return wrap(WinUICanvasGeometry, binding.canvasGeometryCreatePath(adopt(builder)))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICanvasGeometry }
    }
  }
}

expose(exports)
