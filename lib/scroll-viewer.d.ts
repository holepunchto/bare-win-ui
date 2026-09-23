import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIFrameworkElement = require('./framework-element')
import WinUIUIElement = require('./ui-element')

/** An element that scrolls its content, as a `ScrollViewer`. It does not report pointer events. */
interface WinUIScrollViewer extends WinUIFrameworkElement<WinUIScrollViewer.Events> {
  get content(): WinUIUIElement | null
  set content(content: Wrapper | null)

  readonly horizontalOffset: number

  readonly verticalOffset: number

  readonly extentWidth: number

  readonly extentHeight: number

  readonly viewportWidth: number

  readonly viewportHeight: number

  readonly scrollableWidth: number

  readonly scrollableHeight: number

  /** A `SCROLL_MODE` constant. */
  horizontalScrollMode: number

  verticalScrollMode: number

  /** A `SCROLL_BAR_VISIBILITY` constant. */
  horizontalScrollBarVisibility: number

  verticalScrollBarVisibility: number

  /** Scroll and zoom. Pass `null` to leave an offset or the zoom as it is. Returns whether it worked. */
  changeView(
    horizontalOffset: number | null,
    verticalOffset: number | null,
    zoomFactor?: number | null,
    disableAnimation?: boolean
  ): boolean
}

declare class WinUIScrollViewer {
  constructor()

  static readonly SCROLL_MODE: {
    readonly DISABLED: number
    readonly ENABLED: number
    readonly AUTO: number
  }

  static readonly SCROLL_BAR_VISIBILITY: {
    readonly DISABLED: number
    readonly AUTO: number
    readonly HIDDEN: number
    readonly VISIBLE: number
  }
}

declare namespace WinUIScrollViewer {
  export interface Events {
    /** The view scrolled. Read the offsets from the viewer. */
    viewChanged: [event: { isIntermediate: boolean }]
  }
}

export = WinUIScrollViewer
