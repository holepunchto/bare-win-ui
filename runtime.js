require.asset = require('require-asset')

const prebuilds = {}

exports.prebuilds = prebuilds

prebuilds['win32-x64'] = () => {
  return require.asset('./prebuilds/win32-x64/bare.exe', __filename)
}

prebuilds['win32-arm64'] = () => {
  return require.asset('./prebuilds/win32-arm64/bare.exe', __filename)
}
