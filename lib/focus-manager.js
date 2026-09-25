const binding = require('../binding')

// Focus is given to a control and never taken away, so letting go of it is
// moving it on. `FocusManager` is all static methods and has no instance, and
// a desktop app has to say which tree the focus is moving within.
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
