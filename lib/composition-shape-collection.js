const binding = require('../binding')
const { adopt, expose } = require('./handle')
const { hold, drop } = require('./reachable')
const wrap = require('./wrap')
const CompositionShape = require('./composition-shape')
const WinUIObject = require('./object')

module.exports = exports = class WinUICompositionShapeCollection extends WinUIObject {
  get size() {
    return binding.compositionShapeCollectionSize(this._tag)
  }

  getAt(index) {
    return wrap(CompositionShape, binding.compositionShapeCollectionGetAt(this._tag, index))
  }

  indexOf(value) {
    return binding.compositionShapeCollectionIndexOf(this._tag, adopt(value))
  }

  append(value) {
    binding.compositionShapeCollectionAppend(this._tag, adopt(value))
    hold(this, value)
    return this
  }

  insertAt(index, value) {
    binding.compositionShapeCollectionInsertAt(this._tag, index, adopt(value))
    hold(this, value)
    return this
  }

  removeAt(index) {
    const tag = binding.compositionShapeCollectionGetAt(this._tag, index)

    binding.compositionShapeCollectionRemoveAt(this._tag, index)
    drop(this, binding.wrapper(tag))
    return this
  }

  clear() {
    binding.compositionShapeCollectionClear(this._tag)
    this._retained.clear()
    return this
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUICompositionShapeCollection },

      size: this.size
    }
  }
}

expose(exports)
