const binding = require('../binding')
const wrap = require('./wrap')
const WinUIObject = require('./object')

module.exports = exports = class WinUIDisplayArea extends WinUIObject {
  static get primary() {
    return wrap(WinUIDisplayArea, binding.displayAreaPrimary())
  }

  static getFromWindowId(id, fallback = exports.FALLBACK.NEAREST) {
    return wrap(WinUIDisplayArea, binding.displayAreaGetFromWindowId(id, fallback))
  }

  get outerBounds() {
    return binding.displayAreaOuterBounds(this._tag)
  }

  get workArea() {
    return binding.displayAreaWorkArea(this._tag)
  }

  get isPrimary() {
    return binding.displayAreaIsPrimary(this._tag)
  }
}

exports.FALLBACK = {
  NONE: binding.DISPLAY_AREA_FALLBACK_NONE,
  PRIMARY: binding.DISPLAY_AREA_FALLBACK_PRIMARY,
  NEAREST: binding.DISPLAY_AREA_FALLBACK_NEAREST
}
