const EventEmitter = require('bare-events')
const binding = require('../binding')

module.exports = exports = class WinUIWindow extends EventEmitter {
  constructor() {
    super()

    this._handle = binding.windowInit(this)
  }

  get title() {
    return binding.windowTitle(this._handle)
  }

  set title(value) {
    binding.windowTitle(this._handle, value)
  }

  get content() {
    return binding.windowContent(this._handle)
  }

  set content(element) {
    binding.windowContent(this._handle, element._handle)
  }

  activate() {
    binding.windowActivate(this._handle)
    return this
  }

  close() {
    binding.windowClose(this._handle)
    return this
  }

  resize(width, height) {
    binding.windowResize(this._handle, width, height)
    return this
  }

  resizeClient(width, height) {
    binding.windowResizeClient(this._handle, width, height)
    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIWindow }
    }
  }
}
