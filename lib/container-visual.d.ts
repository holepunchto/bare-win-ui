import WinUIVisual = require('./visual')

/** A visual that can hold other visuals, as a `ContainerVisual`. */
interface WinUIContainerVisual extends WinUIVisual {}

declare class WinUIContainerVisual {
  protected constructor()
}

export = WinUIContainerVisual
