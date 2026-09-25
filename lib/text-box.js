const binding = require('../binding')
const Control = require('./control')

module.exports = exports = class WinUITextBox extends Control {
  static _events = {
    textChanging: binding.TEXT_BOX_EVENT_TEXT_CHANGING,
    textChanged: binding.TEXT_BOX_EVENT_TEXT_CHANGED,
    selectionChanged: binding.TEXT_BOX_EVENT_SELECTION_CHANGED,
    gotFocus: binding.TEXT_BOX_EVENT_GOT_FOCUS,
    lostFocus: binding.TEXT_BOX_EVENT_LOST_FOCUS,
    keyDown: binding.TEXT_BOX_EVENT_KEY_DOWN,
    loaded: binding.TEXT_BOX_EVENT_LOADED
  }

  _init() {
    return binding.textBoxInit()
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.textBoxEvents(this)

    binding.textBoxEventMask(this._tag, this._subscription, mask)
  }

  get text() {
    return binding.textBoxText(this._tag)
  }

  set text(value) {
    binding.textBoxText(this._tag, value)
  }

  get placeholderText() {
    return binding.textBoxPlaceholderText(this._tag)
  }

  set placeholderText(value) {
    binding.textBoxPlaceholderText(this._tag, value)
  }

  get isReadOnly() {
    return binding.textBoxIsReadOnly(this._tag)
  }

  set isReadOnly(value) {
    binding.textBoxIsReadOnly(this._tag, value)
  }

  get acceptsReturn() {
    return binding.textBoxAcceptsReturn(this._tag)
  }

  set acceptsReturn(value) {
    binding.textBoxAcceptsReturn(this._tag, value)
  }

  get isSpellCheckEnabled() {
    return binding.textBoxIsSpellCheckEnabled(this._tag)
  }

  set isSpellCheckEnabled(value) {
    binding.textBoxIsSpellCheckEnabled(this._tag, value)
  }

  get selectionStart() {
    return binding.textBoxSelectionStart(this._tag)
  }

  set selectionStart(value) {
    binding.textBoxSelectionStart(this._tag, value)
  }

  get selectionLength() {
    return binding.textBoxSelectionLength(this._tag)
  }

  set selectionLength(value) {
    binding.textBoxSelectionLength(this._tag, value)
  }

  get textWrapping() {
    return binding.textBoxTextWrapping(this._tag)
  }

  set textWrapping(value) {
    binding.textBoxTextWrapping(this._tag, value)
  }

  set inputScope(value) {
    binding.textBoxInputScope(this._tag, value)
  }

  _ontextchanging() {
    this.emit('textChanging')
  }

  _ontextchanged() {
    this.emit('textChanged')
  }

  _onselectionchanged() {
    this.emit('selectionChanged')
  }

  _ongotfocus() {
    this.emit('gotFocus')
  }

  _onlostfocus() {
    this.emit('lostFocus')
  }

  _onkeydown(key) {
    this.emit('keyDown', { key })
  }

  _onloaded() {
    this.emit('loaded')
  }
}

exports.TEXT_WRAPPING = {
  NO_WRAP: binding.TEXT_WRAPPING_NO_WRAP,
  WRAP: binding.TEXT_WRAPPING_WRAP,
  WRAP_WHOLE_WORDS: binding.TEXT_WRAPPING_WRAP_WHOLE_WORDS
}

// The scope names a text box asks the touch keyboard for, which is the same
// question `keyboardType` asks on the platforms that have one.
exports.INPUT_SCOPE_NAME = {
  DEFAULT: 0,
  URL: 1,
  EMAIL_SMTP_ADDRESS: 5,
  NUMBER: 29,
  TELEPHONE_NUMBER: 32,
  DIGITS: 28,
  CURRENCY_AMOUNT: 20
}
