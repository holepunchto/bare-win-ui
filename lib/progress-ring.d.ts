import WinUIControl = require('./control')

/** A spinning busy indicator, as a `ProgressRing`. */
interface WinUIProgressRing extends WinUIControl {
  /** Whether the ring spins. */
  isActive: boolean
}

declare class WinUIProgressRing {
  constructor()
}

export = WinUIProgressRing
