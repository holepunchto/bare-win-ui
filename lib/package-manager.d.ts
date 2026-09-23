import EventEmitter from 'bare-events'

/** Installs app packages, as a `PackageManager`. */
interface WinUIPackageManager {
  /** Install the package at `uri`. Await the result, and listen for `progress`. */
  addPackage(uri: string): WinUIPackageManager.AddPackage
}

declare class WinUIPackageManager {
  constructor()
}

declare namespace WinUIPackageManager {
  interface AddPackageEvents {
    progress: [progress: { percentage: number }]
  }

  interface AddPackage extends EventEmitter<AddPackageEvents>, PromiseLike<void> {}
}

export = WinUIPackageManager
