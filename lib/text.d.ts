/**
 * Measure `text` as a text block would show it, wrapped at `width`, which defaults to `Infinity`.
 * `style.size` of 0 means the default size. Results are cached.
 */
export function measure(
  text: string,
  style?: { family?: string | null; size?: number },
  width?: number
): { width: number; height: number; lines: number }
