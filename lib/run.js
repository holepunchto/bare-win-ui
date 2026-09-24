const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const Brush = require('./brush')
const FontFamily = require('./font-family')
const DependencyObject = require('./dependency-object')

module.exports = exports = class WinUIRun extends DependencyObject {
  static FONT_STYLE = {
    NORMAL: binding.FONT_STYLE_NORMAL,
    OBLIQUE: binding.FONT_STYLE_OBLIQUE,
    ITALIC: binding.FONT_STYLE_ITALIC
  }

  _init() {
    return binding.runInit()
  }

  get text() {
    return binding.runText(this._tag)
  }

  set text(value) {
    binding.runText(this._tag, value)
  }

  get fontSize() {
    return binding.runFontSize(this._tag)
  }

  set fontSize(value) {
    binding.runFontSize(this._tag, value)
  }

  get fontFamily() {
    return wrap(FontFamily, binding.runFontFamily(this._tag))
  }

  set fontFamily(value) {
    binding.runFontFamily(this._tag, adopt(value))
  }

  get fontWeight() {
    return binding.runFontWeight(this._tag)
  }

  set fontWeight(value) {
    binding.runFontWeight(this._tag, value)
  }

  get fontStyle() {
    return binding.runFontStyle(this._tag)
  }

  set fontStyle(value) {
    binding.runFontStyle(this._tag, value)
  }

  get foreground() {
    return wrap(Brush, binding.runForeground(this._tag))
  }

  set foreground(value) {
    binding.runForeground(this._tag, adopt(value))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIRun }
    }
  }
}
