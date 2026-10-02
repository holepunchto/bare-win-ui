const wrap = require('./wrap')

module.exports = exports = function retain(holder, key, Class, tag) {
  const value = wrap(Class, tag)

  holder[key] = value

  return value
}
