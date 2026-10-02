import WinUIObject = require('./object')
import WinUIXamlRoot = require('./xaml-root')

/** A dialog, as a `ContentDialog`. */
interface WinUIContentDialog extends WinUIObject {
  set title(value: string)

  set content(value: string)

  primaryButtonText: string

  secondaryButtonText: string

  closeButtonText: string

  /** The button pressed by Enter, as a `BUTTON` constant. */
  set defaultButton(value: number)

  /** What the dialog is drawn into. It will not open without one: use the `xamlRoot` of the window content. */
  set xamlRoot(root: WinUIXamlRoot)

  /** Show the dialog. `callback` is called with a `RESULT` constant when it closes. */
  showAsync(callback: (result: number) => void): void
}

declare class WinUIContentDialog {
  constructor()

  static readonly BUTTON: {
    readonly NONE: number
    readonly PRIMARY: number
    readonly SECONDARY: number
    readonly CLOSE: number
  }

  static readonly RESULT: {
    readonly NONE: number
    readonly PRIMARY: number
    readonly SECONDARY: number
  }
}

export = WinUIContentDialog
