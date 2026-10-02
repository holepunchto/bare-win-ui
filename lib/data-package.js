const binding = require('../binding')
const wrap = require('./wrap')
const WinUIObject = require('./object')

module.exports = exports = class WinUIDataPackage extends WinUIObject {
  _init() {
    return binding.dataPackageInit()
  }

  setText(text) {
    binding.dataPackageSetText(this._tag, text)

    return this
  }

  get requestedOperation() {
    return binding.dataPackageRequestedOperation(this._tag)
  }

  set requestedOperation(operation) {
    binding.dataPackageRequestedOperation(this._tag, operation)
  }

  getView() {
    const WinUIDataPackageView = require('./data-package-view')

    return wrap(WinUIDataPackageView, binding.dataPackageGetView(this._tag))
  }
}

exports.OPERATION = {
  NONE: binding.DATA_PACKAGE_OPERATION_NONE,
  COPY: binding.DATA_PACKAGE_OPERATION_COPY,
  MOVE: binding.DATA_PACKAGE_OPERATION_MOVE,
  LINK: binding.DATA_PACKAGE_OPERATION_LINK
}
