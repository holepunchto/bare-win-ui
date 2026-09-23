const binding = require('../binding')
const WinUIObject = require('./object')

module.exports = exports = class WinUIContentDialog extends WinUIObject {
  _init() {
    return binding.contentDialogInit()
  }

  set title(value) {
    binding.contentDialogTitle(this._tag, value)
  }

  set content(value) {
    binding.contentDialogContent(this._tag, value)
  }

  get primaryButtonText() {
    return binding.contentDialogPrimaryButtonText(this._tag)
  }

  set primaryButtonText(value) {
    binding.contentDialogPrimaryButtonText(this._tag, value)
  }

  get secondaryButtonText() {
    return binding.contentDialogSecondaryButtonText(this._tag)
  }

  set secondaryButtonText(value) {
    binding.contentDialogSecondaryButtonText(this._tag, value)
  }

  get closeButtonText() {
    return binding.contentDialogCloseButtonText(this._tag)
  }

  set closeButtonText(value) {
    binding.contentDialogCloseButtonText(this._tag, value)
  }

  set defaultButton(value) {
    binding.contentDialogDefaultButton(this._tag, value)
  }

  set xamlRoot(root) {
    binding.contentDialogXamlRoot(this._tag, root._tag)
  }

  showAsync(callback) {
    binding.contentDialogShowAsync(this._tag, callback)
  }
}

exports.BUTTON = {
  NONE: binding.CONTENT_DIALOG_BUTTON_NONE,
  PRIMARY: binding.CONTENT_DIALOG_BUTTON_PRIMARY,
  SECONDARY: binding.CONTENT_DIALOG_BUTTON_SECONDARY,
  CLOSE: binding.CONTENT_DIALOG_BUTTON_CLOSE
}

exports.RESULT = {
  NONE: binding.CONTENT_DIALOG_RESULT_NONE,
  PRIMARY: binding.CONTENT_DIALOG_RESULT_PRIMARY,
  SECONDARY: binding.CONTENT_DIALOG_RESULT_SECONDARY
}
