const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const Brush = require('./brush')
const FontFamily = require('./font-family')
const InlineCollection = require('./inline-collection')
const FrameworkElement = require('./framework-element')

module.exports = exports = class WinUITextBlock extends FrameworkElement {
  static TEXT_ALIGNMENT = {
    CENTER: binding.TEXT_ALIGNMENT_CENTER,
    LEFT: binding.TEXT_ALIGNMENT_LEFT,
    START: binding.TEXT_ALIGNMENT_START,
    RIGHT: binding.TEXT_ALIGNMENT_RIGHT,
    END: binding.TEXT_ALIGNMENT_END,
    JUSTIFY: binding.TEXT_ALIGNMENT_JUSTIFY,
    DETECT_FROM_CONTENT: binding.TEXT_ALIGNMENT_DETECT_FROM_CONTENT
  }

  static TEXT_WRAPPING = {
    NO_WRAP: binding.TEXT_WRAPPING_NO_WRAP,
    WRAP: binding.TEXT_WRAPPING_WRAP,
    WRAP_WHOLE_WORDS: binding.TEXT_WRAPPING_WRAP_WHOLE_WORDS
  }

  _init() {
    return binding.textBlockInit()
  }

  get text() {
    return binding.textBlockText(this._tag)
  }

  set text(value) {
    binding.textBlockText(this._tag, value)
  }

  get fontSize() {
    return binding.textBlockFontSize(this._tag)
  }

  set fontSize(value) {
    binding.textBlockFontSize(this._tag, value)
  }

  get lineHeight() {
    return binding.textBlockLineHeight(this._tag)
  }

  set lineHeight(value) {
    binding.textBlockLineHeight(this._tag, value)
  }

  get fontFamily() {
    return wrap(FontFamily, binding.textBlockFontFamily(this._tag))
  }

  set fontFamily(value) {
    binding.textBlockFontFamily(this._tag, adopt(value))
  }

  get foreground() {
    return wrap(Brush, binding.textBlockForeground(this._tag))
  }

  set foreground(value) {
    binding.textBlockForeground(this._tag, adopt(value))
  }

  get textAlignment() {
    return binding.textBlockTextAlignment(this._tag)
  }

  set textAlignment(value) {
    binding.textBlockTextAlignment(this._tag, value)
  }

  get inlines() {
    return wrap(InlineCollection, binding.textBlockInlines(this._tag))
  }

  get textWrapping() {
    return binding.textBlockTextWrapping(this._tag)
  }

  set textWrapping(value) {
    binding.textBlockTextWrapping(this._tag, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUITextBlock }
    }
  }
}

expose(exports)
