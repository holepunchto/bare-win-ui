const binding = require('../binding')

exports.tryMoveFocus = function tryMoveFocus(element, direction) {
  return binding.focusManagerTryMoveFocus(element._tag, direction)
}

exports.FOCUS_NAVIGATION_DIRECTION = {
  NEXT: binding.FOCUS_NAVIGATION_DIRECTION_NEXT,
  PREVIOUS: binding.FOCUS_NAVIGATION_DIRECTION_PREVIOUS,
  UP: binding.FOCUS_NAVIGATION_DIRECTION_UP,
  DOWN: binding.FOCUS_NAVIGATION_DIRECTION_DOWN,
  LEFT: binding.FOCUS_NAVIGATION_DIRECTION_LEFT,
  RIGHT: binding.FOCUS_NAVIGATION_DIRECTION_RIGHT,
  NONE: binding.FOCUS_NAVIGATION_DIRECTION_NONE
}
