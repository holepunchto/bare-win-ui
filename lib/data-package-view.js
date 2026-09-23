const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUIDataPackageView extends WinUIObject {
  contains(format) {
    return binding.dataPackageViewContains(this._tag, format)
  }

  getTextAsync(callback) {
    binding.dataPackageViewGetTextAsync(this._tag, callback)
  }
}

exports.STANDARD_DATA_FORMATS = {
  TEXT: binding.STANDARD_DATA_FORMATS_TEXT,
  HTML: binding.STANDARD_DATA_FORMATS_HTML,
  RTF: binding.STANDARD_DATA_FORMATS_RTF,
  BITMAP: binding.STANDARD_DATA_FORMATS_BITMAP,
  WEB_LINK: binding.STANDARD_DATA_FORMATS_WEB_LINK,
  APPLICATION_LINK: binding.STANDARD_DATA_FORMATS_APPLICATION_LINK,
  STORAGE_ITEMS: binding.STANDARD_DATA_FORMATS_STORAGE_ITEMS
}
