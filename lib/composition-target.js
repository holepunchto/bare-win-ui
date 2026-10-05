const EventEmitter = require('bare-events')
const binding = require('../binding')

const events = {
  rendering: binding.COMPOSITION_TARGET_EVENT_RENDERING
}

// Every member of `CompositionTarget` is static, its events included, so the
// class itself is what they are listened to on.
const emitter = new EventEmitter()

let subscription = null
let mask = 0

function eventMask(next) {
  if (subscription === null) subscription = binding.compositionTargetEvents(exports)

  binding.compositionTargetEventMask(subscription, (mask = next))
}

emitter
  .on('newListener', (name) => {
    const bit = events[name]

    if (bit === undefined || emitter.listenerCount(name) !== 0) return

    eventMask(mask | bit)
  })
  .on('removeListener', (name) => {
    const bit = events[name]

    if (bit === undefined || emitter.listenerCount(name) !== 0) return

    eventMask(mask & ~bit)
  })

module.exports = exports = class WinUICompositionTarget {
  static on(name, fn) {
    emitter.on(name, fn)
    return this
  }

  static once(name, fn) {
    emitter.once(name, fn)
    return this
  }

  static off(name, fn) {
    emitter.off(name, fn)
    return this
  }

  static _onrendering(renderingTime) {
    emitter.emit('rendering', { renderingTime })
  }
}
