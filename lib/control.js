const binding = require('../binding')
const { adopt, expose } = require('./handle')
const wrap = require('./wrap')
const retain = require('./retain')
const Brush = require('./brush')
const FrameworkElement = require('./framework-element')

module.exports = exports = class WinUIControl extends FrameworkElement {
  get isEnabled() {
    return binding.controlIsEnabled(this._tag)
  }

  set isEnabled(value) {
    binding.controlIsEnabled(this._tag, value)
  }

  get background() {
    return retain(this, '_background', Brush, binding.controlBackground(this._tag))
  }

  set background(value) {
    binding.controlBackground(this._tag, value === null ? null : adopt(value))

    this._background = value
  }

  get borderBrush() {
    return retain(this, '_borderBrush', Brush, binding.controlBorderBrush(this._tag))
  }

  set borderBrush(value) {
    binding.controlBorderBrush(this._tag, value === null ? null : adopt(value))

    this._borderBrush = value
  }

  get useSystemFocusVisuals() {
    return binding.controlUseSystemFocusVisuals(this._tag)
  }

  set useSystemFocusVisuals(value) {
    binding.controlUseSystemFocusVisuals(this._tag, value)
  }

  get foreground() {
    return retain(this, '_foreground', Brush, binding.controlForeground(this._tag))
  }

  set foreground(value) {
    binding.controlForeground(this._tag, value === null ? null : adopt(value))

    this._foreground = value
  }

  set borderThickness(value) {
    binding.controlBorderThickness(this._tag, value)
  }

  set padding(value) {
    binding.controlPadding(this._tag, value)
  }

  set cornerRadius(value) {
    binding.controlCornerRadius(this._tag, value)
  }

  templateChild(name) {
    return wrap(FrameworkElement, binding.controlTemplateChild(this._tag, name))
  }

  focus(state = exports.FOCUS_STATE.PROGRAMMATIC) {
    return binding.controlFocus(this._tag, state)
  }
}

exports.FOCUS_STATE = {
  UNFOCUSED: binding.FOCUS_STATE_UNFOCUSED,
  POINTER: binding.FOCUS_STATE_POINTER,
  KEYBOARD: binding.FOCUS_STATE_KEYBOARD,
  PROGRAMMATIC: binding.FOCUS_STATE_PROGRAMMATIC
}

expose(exports)
