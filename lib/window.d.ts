import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIObject = require('./object')
import WinUIAppWindow = require('./app-window')
import WinUIUIElement = require('./ui-element')

/** A window, as a `Window`. */
interface WinUIWindow extends WinUIObject<WinUIWindow.Events> {
  title: string

  /** The element the window shows. */
  get content(): WinUIUIElement | null
  set content(content: Wrapper | null)

  /** The client area of the window. */
  readonly bounds: { x: number; y: number; width: number; height: number }

  /** The window as the system sees it, in physical pixels. */
  readonly appWindow: WinUIAppWindow

  /** Show the window and bring it to the front. */
  activate(): this

  close(): this

  /** Resize the whole window, in physical pixels. */
  resize(width: number, height: number): this

  /** Resize the client area of the window, in physical pixels. */
  resizeClient(width: number, height: number): this
}

declare class WinUIWindow {
  constructor()
}

declare namespace WinUIWindow {
  export interface Events {
    sizeChanged: [size: { width: number; height: number }]
  }
}

export = WinUIWindow
