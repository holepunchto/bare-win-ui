import EventEmitter from 'bare-events'
import { tag, handle, Handle } from 'bare-winrt-registry'

/**
 * The base of every WinRT object in this module. Objects that have events emit them as ordinary
 * events, and WinRT is only asked to report an event while something listens to it. Lengths are
 * in device independent pixels unless they say otherwise, and colours are `{ a, r, g, b }`
 * objects with components from 0 to 255.
 */
interface WinUIObject<M extends Record<keyof M, unknown[]> = {}> extends EventEmitter<M> {
  readonly [tag]: number

  readonly [handle]: Handle
}

declare class WinUIObject<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = WinUIObject
