const binding = require('../binding')
const { expose } = require('./handle')
const Control = require('./control')

// Secure entry is a control of its own here, as it is on AppKit, and it keeps
// its text in `Password` rather than `Text` and offers no selection at all.
module.exports = exports = class WinUIPasswordBox extends Control {
  static _events = {
    passwordChanged: binding.PASSWORD_BOX_EVENT_PASSWORD_CHANGED,
    gotFocus: binding.PASSWORD_BOX_EVENT_GOT_FOCUS,
    lostFocus: binding.PASSWORD_BOX_EVENT_LOST_FOCUS,
    loaded: binding.PASSWORD_BOX_EVENT_LOADED
  }

  _init() {
    return binding.passwordBoxInit()
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.passwordBoxEvents(this)

    binding.passwordBoxEventMask(this._tag, this._subscription, mask)
  }

  set passwordRevealMode(value) {
    binding.passwordBoxPasswordRevealMode(this._tag, value)
  }

  get password() {
    return binding.passwordBoxPassword(this._tag)
  }

  set password(value) {
    binding.passwordBoxPassword(this._tag, value)
  }

  get placeholderText() {
    return binding.passwordBoxPlaceholderText(this._tag)
  }

  set placeholderText(value) {
    binding.passwordBoxPlaceholderText(this._tag, value)
  }

  _onpasswordchanged() {
    this.emit('passwordChanged')
  }

  _ongotfocus() {
    this.emit('gotFocus')
  }

  _onlostfocus() {
    this.emit('lostFocus')
  }

  _onloaded() {
    this.emit('loaded')
  }
}

exports.PASSWORD_REVEAL_MODE = {
  PEEK: binding.PASSWORD_REVEAL_MODE_PEEK,
  HIDDEN: binding.PASSWORD_REVEAL_MODE_HIDDEN,
  VISIBLE: binding.PASSWORD_REVEAL_MODE_VISIBLE
}

expose(exports)
