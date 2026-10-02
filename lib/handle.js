const binding = require('../binding')
const registry = require('bare-winrt-registry')

exports.adopt = function adopt(object) {
  return registry.adopt(binding, object)
}
