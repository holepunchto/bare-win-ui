/** The `HWND` of the window with the `WindowId` `id`, or `0n` if there is none. */
export function getWindowFromWindowId(id: bigint): bigint

/** The `WindowId` of the window with the `HWND` `window`, or `0n` if there is none. */
export function getWindowIdFromWindow(window: bigint): bigint
