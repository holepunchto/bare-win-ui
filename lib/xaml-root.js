const binding = require('../binding')
const wrap = require('./wrap')
const WinUIObject = require('./object')
const WinUIContentIslandEnvironment = require('./content-island-environment')

module.exports = exports = class WinUIXamlRoot extends WinUIObject {
  static _events = {
    changed: binding.XAML_ROOT_EVENT_CHANGED
  }

  get size() {
    return binding.xamlRootSize(this._tag)
  }

  get rasterizationScale() {
    return binding.xamlRootRasterizationScale(this._tag)
  }

  get contentIslandEnvironment() {
    return wrap(WinUIContentIslandEnvironment, binding.xamlRootContentIslandEnvironment(this._tag))
  }

  get isHostVisible() {
    return binding.xamlRootIsHostVisible(this._tag)
  }

  _eventMask(mask) {
    if (this._subscription === undefined) this._subscription = binding.xamlRootEvents(this)

    binding.xamlRootEventMask(this._tag, this._subscription, mask)
  }

  _onchanged() {
    this.emit('changed')
  }
}
