const binding = require('../binding')
const { expose } = require('./handle')
const Control = require('./control')

module.exports = exports = class WinUIToggleSwitch extends Control {
  static _events = {
    toggled: binding.TOGGLE_SWITCH_EVENT_TOGGLED,
    loaded: binding.TOGGLE_SWITCH_EVENT_LOADED
  }

  _init() {
    return binding.toggleSwitchInit()
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.toggleSwitchEvents(this)

    binding.toggleSwitchEventMask(this._tag, this._subscription, mask)
  }

  get isOn() {
    return binding.toggleSwitchIsOn(this._tag)
  }

  set isOn(value) {
    binding.toggleSwitchIsOn(this._tag, value)
  }

  content(on, off) {
    binding.toggleSwitchContent(this._tag, on, off)

    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIToggleSwitch }
    }
  }

  _ontoggled() {
    this.emit('toggled')
  }

  _onloaded() {
    this.emit('loaded')
  }
}

expose(exports)
