const binding = require('../binding')
const { adopt } = require('./handle')
const retain = require('./retain')
const FrameworkElement = require('./framework-element')
const ImageSource = require('./image-source')

// A `BitmapImage` decodes off the thread that set it, so what an `Image` knows
// about a picture it has been given arrives through these rather than from the
// call that gave it.
module.exports = exports = class WinUIImage extends FrameworkElement {
  static STRETCH = {
    NONE: binding.STRETCH_NONE,
    FILL: binding.STRETCH_FILL,
    UNIFORM: binding.STRETCH_UNIFORM,
    UNIFORM_TO_FILL: binding.STRETCH_UNIFORM_TO_FILL
  }

  static _events = {
    imageOpened: binding.IMAGE_EVENT_IMAGE_OPENED,
    imageFailed: binding.IMAGE_EVENT_IMAGE_FAILED
  }

  _init() {
    return binding.imageInit()
  }

  get source() {
    return retain(this, '_source', ImageSource, binding.imageSource(this._tag))
  }

  set source(value) {
    binding.imageSource(this._tag, value === null ? null : adopt(value))

    this._source = value
  }

  get stretch() {
    return binding.imageStretch(this._tag)
  }

  set stretch(value) {
    binding.imageStretch(this._tag, value)
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.imageEvents(this)

    binding.imageEventMask(this._tag, this._subscription, mask)
  }

  _onimageopened() {
    this.emit('imageOpened')
  }

  _onimagefailed(errorMessage) {
    this.emit('imageFailed', { errorMessage })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIImage }
    }
  }
}
