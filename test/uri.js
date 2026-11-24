const { test } = require('bare-tap')
const { BitmapImage, PackageManager, WebView2 } = require('..')

const uri = 'https://attacker.example\0.trusted.example'

test('rejects URIs with a NUL', async (t) => {
  const image = new BitmapImage()

  t.throws(() => {
    image.uriSource = uri
  }, TypeError)

  t.throws(() => new PackageManager().addPackage(uri), TypeError)

  const view = new WebView2()

  t.throws(() => {
    view.source = uri
  }, TypeError)

  await t.rejects(() => view.navigate(uri), TypeError)
})
