import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIDependencyObject = require('./dependency-object')
import WinUIBrush = require('./brush')
import WinUIFontFamily = require('./font-family')

/** A run of styled text in a text block, as a `Run`. */
interface WinUIRun extends WinUIDependencyObject {
  text: string

  fontSize: number

  /** `TEXT_DECORATIONS` flags combined with `|`. */
  set textDecorations(value: number)

  /** The space between characters, in thousandths of the font size. */
  characterSpacing: number

  get fontFamily(): WinUIFontFamily | null
  set fontFamily(family: Wrapper | null)

  /** The weight, from 100 (thin) to 900 (black). */
  fontWeight: number

  /** A `FONT_STYLE` constant. */
  fontStyle: number

  get foreground(): WinUIBrush | null
  set foreground(brush: Wrapper | null)
}

declare class WinUIRun {
  constructor()

  static readonly FONT_STYLE: {
    readonly NORMAL: number
    readonly OBLIQUE: number
    readonly ITALIC: number
  }

  static readonly TEXT_DECORATIONS: {
    readonly NONE: number
    readonly UNDERLINE: number
    readonly STRIKETHROUGH: number
  }
}

export = WinUIRun
