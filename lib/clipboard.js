const binding = require('../binding')
const wrap = require('./wrap')
const WinUIDataPackage = require('./data-package')
const WinUIDataPackageView = require('./data-package-view')

exports.getContent = function getContent() {
  return wrap(WinUIDataPackageView, binding.clipboardGetContent())
}

exports.setContent = function setContent(dataPackage) {
  binding.clipboardSetContent(dataPackage._tag)
}

exports.clear = function clear() {
  binding.clipboardClear()
}

exports.flush = function flush() {
  binding.clipboardFlush()
}

exports.DataPackage = WinUIDataPackage
