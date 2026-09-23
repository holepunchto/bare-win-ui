import WinUIDataPackage = require('./data-package')
import WinUIDataPackageView = require('./data-package-view')

/** What is on the clipboard, or `null`. */
export function getContent(): WinUIDataPackageView | null

export function setContent(dataPackage: WinUIDataPackage): void

export function clear(): void

/** Keep the data on the clipboard after the app exits. */
export function flush(): void

export { WinUIDataPackage as DataPackage }
