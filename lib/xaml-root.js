const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUIXamlRoot extends WinUIObject {
  get size() {
    return binding.xamlRootSize(this._tag)
  }

  get rasterizationScale() {
    return binding.xamlRootRasterizationScale(this._tag)
  }

  get isHostVisible() {
    return binding.xamlRootIsHostVisible(this._tag)
  }
}
