const binding = require('../binding')
const { expose } = require('./handle')
const ImageSource = require('./image-source')

module.exports = exports = class WinUIBitmapSource extends ImageSource {
  get pixelWidth() {
    return binding.bitmapSourcePixelWidth(this._tag)
  }

  get pixelHeight() {
    return binding.bitmapSourcePixelHeight(this._tag)
  }
}

expose(exports)
