const binding = require('../binding')
const { adopt } = require('./handle')
const { hold, drop } = require('./reachable')
const wrap = require('./wrap')
const UIElement = require('./ui-element')
const WinUIObject = require('./object')

module.exports = exports = class WinUIUIElementCollection extends WinUIObject {
  get size() {
    return binding.uiElementCollectionSize(this._tag)
  }

  getAt(index) {
    return wrap(UIElement, binding.uiElementCollectionGetAt(this._tag, index))
  }

  indexOf(value) {
    return binding.uiElementCollectionIndexOf(this._tag, adopt(value))
  }

  append(value) {
    binding.uiElementCollectionAppend(this._tag, adopt(value))
    hold(this, value)
    return this
  }

  insertAt(index, value) {
    binding.uiElementCollectionInsertAt(this._tag, index, adopt(value))
    hold(this, value)
    return this
  }

  removeAt(index) {
    const tag = binding.uiElementCollectionGetAt(this._tag, index)

    binding.uiElementCollectionRemoveAt(this._tag, index)
    drop(this, binding.wrapper(tag))
    return this
  }

  clear() {
    binding.uiElementCollectionClear(this._tag)
    this._retained.clear()
    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIUIElementCollection },

      size: this.size
    }
  }
}
