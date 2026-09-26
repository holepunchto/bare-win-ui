const binding = require('../binding')
const { expose } = require('./handle')
const BitmapSource = require('./bitmap-source')

module.exports = exports = class WinUIBitmapImage extends BitmapSource {
  _init() {
    return binding.bitmapImageInit()
  }

  get uriSource() {
    return binding.bitmapImageUriSource(this._tag)
  }

  set uriSource(value) {
    binding.bitmapImageUriSource(this._tag, value)
  }
}

expose(exports)
