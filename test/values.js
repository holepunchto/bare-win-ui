const { test } = require('bare-tap')
const { BitmapImage, Image } = require('..')
const Clipboard = require('../lib/clipboard')
const DataPackageView = require('../lib/data-package-view')
const UISettings = require('../lib/ui-settings')
const { mount } = require('./helpers')

const { TEXT } = DataPackageView.STANDARD_DATA_FORMATS

test('round trips text through the clipboard', async (t) => {
  await mount(t, new Image())

  const data = new Clipboard.DataPackage()

  data.requestedOperation = Clipboard.DataPackage.OPERATION.COPY
  data.setText('bare-win-ui')

  t.equal(data.requestedOperation, Clipboard.DataPackage.OPERATION.COPY, 'an operation')

  Clipboard.setContent(data)

  const content = Clipboard.getContent()

  t.equal(content.contains(TEXT), true, 'holds text')

  const read = await new Promise((resolve, reject) => {
    content.getTextAsync((err, text) => (err ? reject(new Error(err)) : resolve(text)))
  })

  t.equal(read, 'bare-win-ui')
})

test('reports an image that cannot be read', async (t) => {
  const image = new Image()
  const source = new BitmapImage()

  source.uriSource = 'file:///C:/no/such/file.png'

  t.equal(source.uriSource, 'file:///C:/no/such/file.png', 'the address')

  image.stretch = Image.STRETCH.UNIFORM
  image.source = source

  t.equal(image.stretch, Image.STRETCH.UNIFORM, 'stretch')
  t.ok(image.source === source, 'same source wrapper')

  const failed = new Promise((resolve) => image.once('imageFailed', resolve))

  await mount(t, image)

  const { errorMessage } = await failed

  t.equal(typeof errorMessage, 'string', 'with a message')
})

test('a bitmap reports its own decode', async (t) => {
  const image = new Image()
  const source = new BitmapImage()

  const failed = new Promise((resolve) => source.once('imageFailed', resolve))

  image.source = source
  source.uriSource = 'file:///C:/no/such/file.png'

  await mount(t, image)

  const { errorMessage } = await failed

  t.equal(typeof errorMessage, 'string', 'with a message')
})

test('reads the text scale', (t) => {
  t.ok(new UISettings().textScaleFactor >= 1)
})
