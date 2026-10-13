const binding = require('../binding')

exports.getWindowFromWindowId = function getWindowFromWindowId(id) {
  return binding.win32InteropGetWindowFromWindowId(id)
}

exports.getWindowIdFromWindow = function getWindowIdFromWindow(window) {
  return binding.win32InteropGetWindowIdFromWindow(window)
}
