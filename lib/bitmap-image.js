const binding = require('../binding')
const BitmapSource = require('./bitmap-source')

module.exports = exports = class WinUIBitmapImage extends BitmapSource {
  static _events = {
    imageOpened: binding.BITMAP_IMAGE_EVENT_IMAGE_OPENED,
    imageFailed: binding.BITMAP_IMAGE_EVENT_IMAGE_FAILED
  }

  _init() {
    return binding.bitmapImageInit()
  }

  get uriSource() {
    return binding.bitmapImageUriSource(this._tag)
  }

  set uriSource(value) {
    binding.bitmapImageUriSource(this._tag, value)
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.bitmapImageEvents(this)

    binding.bitmapImageEventMask(this._tag, this._subscription, mask)
  }

  _onimageopened() {
    this.emit('imageOpened')
  }

  _onimagefailed(errorMessage) {
    this.emit('imageFailed', { errorMessage })
  }
}
