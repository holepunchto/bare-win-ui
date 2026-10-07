const { test } = require('bare-tap')
const { Canvas, Window } = require('..')
const Application = require('../lib/application')
const DisplayArea = require('../lib/display-area')
const { mount } = require('./helpers')

test('sets the title', (t) => {
  const window = new Window()

  window.title = 'Hello'

  t.equal(window.title, 'Hello')
})

test('keeps the content wrapper', (t) => {
  const window = new Window()
  const canvas = new Canvas()

  t.equal(window.content, null, 'no content')

  window.content = canvas

  t.ok(window.content === canvas, 'same wrapper')

  window.content = null

  t.equal(window.content, null, 'removed')
})

test('resizes the client area', async (t) => {
  const window = await mount(t, new Canvas())

  const sizes = []

  window.on('sizeChanged', (size) => sizes.push(size))

  const scale = window.content.xamlRoot.rasterizationScale

  window.resizeClient(Math.round(500 * scale), Math.round(400 * scale))

  t.teardown(() => window.resizeClient(Math.round(400 * scale), Math.round(300 * scale)))

  t.deepStrictEqual(
    { width: window.bounds.width, height: window.bounds.height },
    { width: 500, height: 400 },
    'client size'
  )
  t.deepStrictEqual(sizes[sizes.length - 1], { width: 500, height: 400 }, 'emitted')
})

test('is seen by the system in physical pixels', async (t) => {
  const window = await mount(t, new Canvas())

  const appWindow = window.appWindow
  const scale = window.content.xamlRoot.rasterizationScale

  t.ok(window.appWindow === appWindow, 'same wrapper')
  t.ok(appWindow.id !== 0, 'an id')
  t.ok(appWindow.size.width >= window.bounds.width * scale, 'at least the client area')
})

test('is on a display', async (t) => {
  const window = await mount(t, new Canvas())

  const area = DisplayArea.getFromWindowId(window.appWindow.id)

  t.ok(area !== null, 'a display')
  t.ok(area.workArea.height <= area.outerBounds.height, 'the work area is within the bounds')
  t.ok(DisplayArea.primary.isPrimary, 'a primary display')
})

test('belongs to an application', (t) => {
  const application = Application.current

  t.ok(application !== null, 'started by the runtime')
  t.ok(Application.current === application, 'same wrapper')

  const { ON_LAST_WINDOW_CLOSE, ON_EXPLICIT_SHUTDOWN } = Application.DISPATCHER_SHUTDOWN_MODE

  t.equal(application.dispatcherShutdownMode, ON_LAST_WINDOW_CLOSE, 'shuts down with its windows')

  application.dispatcherShutdownMode = ON_EXPLICIT_SHUTDOWN

  t.teardown(() => {
    application.dispatcherShutdownMode = ON_LAST_WINDOW_CLOSE
  })

  t.equal(application.dispatcherShutdownMode, ON_EXPLICIT_SHUTDOWN, 'only when told to')
})

test('closes a second window', async (t) => {
  await mount(t, new Canvas())

  const window = new Window()

  window.activate()
  window.close()

  t.pass('the app is still running')
})
