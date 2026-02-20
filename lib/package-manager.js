const EventEmitter = require('bare-events')
const binding = require('../binding')

module.exports = class WinUIPackageManager {
  constructor() {
    this._handle = binding.packageManagerInit()
  }

  addPackage(uri) {
    return new WinUIPackageManagerAddPackage(this, uri)
  }
}

class WinUIPackageManagerAddPackage extends EventEmitter {
  constructor(packageManager, uri) {
    super()

    this._packageManager = packageManager

    this._completed = Promise.withResolvers()

    this._handle = binding.packageManagerAddPackage(packageManager._handle, uri, this, this._onprogress, this._oncompleted)
  }

  then(resolve, reject) {
    return this._completed.promise.then(resolve, reject)
  }

  _onprogress(progress) {
    this.emit('progress', progress)
  }

  _oncompleted(err) {
    if (err) {
      this._completed.reject(new Error(err))
    } else {
      this._completed.resolve()
    }
  }
}
