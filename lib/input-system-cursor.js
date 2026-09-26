const binding = require('../binding')
const { expose } = require('./handle')
const wrap = require('./wrap')
const WinUIInputCursor = require('./input-cursor')

module.exports = exports = class WinUIInputSystemCursor extends WinUIInputCursor {
  static create(shape) {
    return wrap(WinUIInputSystemCursor, binding.inputSystemCursorCreate(shape))
  }

  get cursorShape() {
    return binding.inputSystemCursorCursorShape(this._tag)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: WinUIInputSystemCursor }
    }
  }
}

exports.SHAPE = {
  ARROW: binding.INPUT_SYSTEM_CURSOR_SHAPE_ARROW,
  CROSS: binding.INPUT_SYSTEM_CURSOR_SHAPE_CROSS,
  HAND: binding.INPUT_SYSTEM_CURSOR_SHAPE_HAND,
  HELP: binding.INPUT_SYSTEM_CURSOR_SHAPE_HELP,
  IBEAM: binding.INPUT_SYSTEM_CURSOR_SHAPE_IBEAM,
  SIZE_ALL: binding.INPUT_SYSTEM_CURSOR_SHAPE_SIZE_ALL,
  SIZE_NORTHEAST_SOUTHWEST: binding.INPUT_SYSTEM_CURSOR_SHAPE_SIZE_NORTHEAST_SOUTHWEST,
  SIZE_NORTH_SOUTH: binding.INPUT_SYSTEM_CURSOR_SHAPE_SIZE_NORTH_SOUTH,
  SIZE_NORTHWEST_SOUTHEAST: binding.INPUT_SYSTEM_CURSOR_SHAPE_SIZE_NORTHWEST_SOUTHEAST,
  SIZE_WEST_EAST: binding.INPUT_SYSTEM_CURSOR_SHAPE_SIZE_WEST_EAST,
  UNIVERSAL_NO: binding.INPUT_SYSTEM_CURSOR_SHAPE_UNIVERSAL_NO,
  UP_ARROW: binding.INPUT_SYSTEM_CURSOR_SHAPE_UP_ARROW,
  WAIT: binding.INPUT_SYSTEM_CURSOR_SHAPE_WAIT,
  PIN: binding.INPUT_SYSTEM_CURSOR_SHAPE_PIN,
  PERSON: binding.INPUT_SYSTEM_CURSOR_SHAPE_PERSON,
  APP_STARTING: binding.INPUT_SYSTEM_CURSOR_SHAPE_APP_STARTING
}

expose(exports)
