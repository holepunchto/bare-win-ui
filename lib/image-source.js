const { expose } = require('./handle')
const DependencyObject = require('./dependency-object')

module.exports = exports = class WinUIImageSource extends DependencyObject {}

expose(exports)
