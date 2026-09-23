import { tag, handle, Handle, Wrapper } from 'bare-winrt-registry'
import WinUIFrameworkElement = require('./framework-element')
import WinUIBrush = require('./brush')
import WinUIFontFamily = require('./font-family')
import WinUIInlineCollection = require('./inline-collection')

/** An element that shows text, as a `TextBlock`. */
interface WinUITextBlock extends WinUIFrameworkElement {
  text: string

  fontSize: number

  /** The height of each line. 0 means the height of the font. */
  lineHeight: number

  get fontFamily(): WinUIFontFamily | null
  set fontFamily(family: Wrapper | null)

  get foreground(): WinUIBrush | null
  set foreground(brush: Wrapper | null)

  /** A `TEXT_ALIGNMENT` constant. */
  textAlignment: number

  /** The runs of styled text the block shows. */
  readonly inlines: WinUIInlineCollection

  /** A `TEXT_WRAPPING` constant. */
  textWrapping: number

  /** The most lines to show. 0 means no limit. */
  maxLines: number

  /** How text that does not fit is cut off, as a `TEXT_TRIMMING` constant. */
  textTrimming: number
}

declare class WinUITextBlock {
  constructor()

  static readonly TEXT_ALIGNMENT: {
    readonly CENTER: number
    readonly LEFT: number
    readonly START: number
    readonly RIGHT: number
    readonly END: number
    readonly JUSTIFY: number
    readonly DETECT_FROM_CONTENT: number
  }

  static readonly TEXT_WRAPPING: {
    readonly NO_WRAP: number
    readonly WRAP: number
    readonly WRAP_WHOLE_WORDS: number
  }

  static readonly TEXT_TRIMMING: {
    readonly NONE: number
    readonly CLIP: number
    readonly WORD_ELLIPSIS: number
    readonly CHARACTER_ELLIPSIS: number
  }
}

export = WinUITextBlock
