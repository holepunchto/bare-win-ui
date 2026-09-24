const binding = require('../binding')
const { adopt } = require('./handle')
const { hold } = require('./reachable')
const WinUIObject = require('./object')

module.exports = exports = class WinUIInlineCollection extends WinUIObject {
  get size() {
    return binding.inlineCollectionSize(this._tag)
  }

  append(item) {
    binding.inlineCollectionAppend(this._tag, adopt(item))
    hold(this, item)

    return this
  }

  clear() {
    binding.inlineCollectionClear(this._tag)
    this._retained.clear()

    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIInlineCollection }
    }
  }
}
