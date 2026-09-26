const binding = require('../binding')
const { adopt, expose } = require('./handle')
const retain = require('./retain')
const UIElement = require('./ui-element')
const WinUIObject = require('./object')

module.exports = exports = class WinUIWindow extends WinUIObject {
  static _events = {
    sizeChanged: binding.WINDOW_EVENT_SIZE_CHANGED
  }

  _init() {
    return binding.windowInit()
  }

  get title() {
    return binding.windowTitle(this._tag)
  }

  set title(value) {
    binding.windowTitle(this._tag, value)
  }

  get content() {
    return retain(this, '_content', UIElement, binding.windowContent(this._tag))
  }

  set content(value) {
    binding.windowContent(this._tag, adopt(value))

    this._content = value
  }

  get bounds() {
    return binding.windowBounds(this._tag)
  }

  activate() {
    binding.windowActivate(this._tag)
    return this
  }

  close() {
    binding.windowClose(this._tag)
    return this
  }

  resize(width, height) {
    binding.windowResize(this._tag, width, height)
    return this
  }

  resizeClient(width, height) {
    binding.windowResizeClient(this._tag, width, height)
    return this
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.windowEvents(this)

    binding.windowEventMask(this._tag, this._subscription, mask)
  }

  _onsizechanged(width, height) {
    this.emit('sizeChanged', { width, height })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIWindow },

      title: this.title,
      bounds: this.bounds
    }
  }
}

expose(exports)
