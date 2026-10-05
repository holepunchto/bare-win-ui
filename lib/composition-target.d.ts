/** What frames are composed for, as `CompositionTarget`. Every member is static. */
declare class WinUICompositionTarget {
  protected constructor()

  static on<K extends keyof WinUICompositionTarget.Events>(
    name: K,
    fn: (...args: WinUICompositionTarget.Events[K]) => void
  ): typeof WinUICompositionTarget

  static once<K extends keyof WinUICompositionTarget.Events>(
    name: K,
    fn: (...args: WinUICompositionTarget.Events[K]) => void
  ): typeof WinUICompositionTarget

  static off<K extends keyof WinUICompositionTarget.Events>(
    name: K,
    fn: (...args: WinUICompositionTarget.Events[K]) => void
  ): typeof WinUICompositionTarget
}

declare namespace WinUICompositionTarget {
  export interface Events {
    /** A frame is about to be rendered. `renderingTime` is when, in milliseconds. */
    rendering: [event: { renderingTime: number }]
  }
}

export = WinUICompositionTarget
