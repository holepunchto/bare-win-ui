const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const Pointer = require('bare-pointer')
const { Canvas, FrameworkElement, SolidColorBrush, TextBlock } = require('..')
const { mount } = require('./helpers')

const { HORIZONTAL_ALIGNMENT, VERTICAL_ALIGNMENT, ELEMENT_THEME } = FrameworkElement

test('builds a hierarchy', async (t) => {
  const parent = new Canvas()
  const a = new TextBlock()
  const b = new TextBlock()
  const c = new TextBlock()

  t.equal(parent.children.size, 0, 'no children')

  parent.children.append(a)
  parent.children.append(c)
  parent.children.insertAt(1, b)

  t.equal(parent.children.size, 3, 'three children')
  t.ok(parent.children.getAt(1) === b, 'inserted')
  t.equal(parent.children.indexOf(c), 2, 'index')

  // An element only has a parent once it is part of a tree that is shown.
  await mount(t, parent)

  t.ok(a.parent === parent, 'same parent wrapper')

  parent.children.removeAt(1)

  t.equal(b.parent, null, 'removed')
  t.equal(parent.children.indexOf(b), -1, 'no longer a child')

  parent.children.clear()

  t.equal(parent.children.size, 0, 'cleared')
})

test('keeps the children wrapper', (t) => {
  const parent = new Canvas()

  t.ok(parent.children === parent.children)
})

test('sets the common properties', (t) => {
  const element = new TextBlock()

  t.equal(element.opacity, 1, 'opaque')
  t.equal(element.isHitTestVisible, true, 'hit test visible')
  t.ok(Number.isNaN(element.width), 'automatic width')
  t.ok(Number.isNaN(element.height), 'automatic height')

  element.opacity = 0.5
  element.isHitTestVisible = false
  element.width = 30
  element.height = 40
  element.horizontalAlignment = HORIZONTAL_ALIGNMENT.RIGHT
  element.verticalAlignment = VERTICAL_ALIGNMENT.BOTTOM

  t.equal(element.opacity, 0.5, 'translucent')
  t.equal(element.isHitTestVisible, false, 'not hit test visible')
  t.equal(element.width, 30, 'width')
  t.equal(element.height, 40, 'height')
  t.equal(element.horizontalAlignment, HORIZONTAL_ALIGNMENT.RIGHT, 'horizontal alignment')
  t.equal(element.verticalAlignment, VERTICAL_ALIGNMENT.BOTTOM, 'vertical alignment')
})

test('measures what it wants', (t) => {
  const text = new TextBlock()

  text.text = 'Hello'
  text.measure({ width: Infinity, height: Infinity })

  const short = text.desiredSize

  t.ok(short.width > 0 && short.height > 0, 'has a size')

  text.text = 'Hello, world'
  text.measure({ width: Infinity, height: Infinity })

  t.ok(text.desiredSize.width > short.width, 'wider when longer')
})

test('places children on a canvas', async (t) => {
  const canvas = new Canvas()
  const child = new Canvas()

  child.width = 30
  child.height = 40

  Canvas.setLeft(child, 10)
  Canvas.setTop(child, 20)
  Canvas.setZIndex(child, 1)

  t.equal(Canvas.getLeft(child), 10, 'left')
  t.equal(Canvas.getTop(child), 20, 'top')

  canvas.children.append(child)

  await mount(t, canvas)

  t.equal(child.actualWidth, 30, 'laid out at its width')
  t.equal(child.actualHeight, 40, 'and height')

  const transform = child.transformToVisual(canvas)

  t.deepStrictEqual(transform.transformPoint(5, 5), { x: 15, y: 25 }, 'to the canvas')
  t.deepStrictEqual(
    child.transformToVisual(null).transformPoint(5, 5),
    { x: 15, y: 25 },
    'to the root the canvas fills'
  )
  t.deepStrictEqual(transform.inverse.transformPoint(15, 25), { x: 5, y: 5 }, 'and back')
  t.deepStrictEqual(
    transform.transformBounds(0, 0, 30, 40),
    { x: 10, y: 20, width: 30, height: 40 },
    'bounds'
  )
})

test('reports the pointer over an element', async (t) => {
  const canvas = new Canvas()
  const box = new Canvas()

  // A panel without a background is not hit tested.
  box.background = new SolidColorBrush({ color: { a: 255, r: 200, g: 200, b: 200 } })
  box.width = 200
  box.height = 150

  Canvas.setLeft(box, 40)
  Canvas.setTop(box, 30)

  canvas.children.append(box)

  await mount(t, canvas)

  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const events = []

  // Input lands on whole physical pixels, which a DIP is not always a whole
  // number of.
  const point = ({ x, y }) => [Math.round(x), Math.round(y)]

  box.on('pointerPressed', (event) => events.push(['pointerPressed', ...point(event)]))
  box.on('pointerMoved', (event) => {
    if (event.isInContact) events.push(['pointerMoved', ...point(event)])
  })
  box.on('pointerReleased', (event) => events.push(['pointerReleased', ...point(event)]))

  await pointer.down(box, 10, 10)
  await pointer.move(box, 50, 40)
  await pointer.move(box, 90, 70)
  await pointer.up()

  t.deepStrictEqual(events, [
    ['pointerPressed', 10, 10],
    ['pointerMoved', 50, 40],
    ['pointerMoved', 90, 70],
    ['pointerReleased', 90, 70]
  ])
})

test('is drawn into a XAML root once loaded', async (t) => {
  const canvas = new Canvas()

  t.equal(canvas.xamlRoot, null, 'none before')

  const window = await mount(t, canvas)

  const root = canvas.xamlRoot

  t.ok(root !== null, 'a root')
  t.equal(root.isHostVisible, true, 'visible')
  t.ok(root.rasterizationScale >= 1, 'a scale')
  t.deepStrictEqual(
    root.size,
    { width: window.bounds.width, height: window.bounds.height },
    'the size of the window'
  )
  t.equal(canvas.actualWidth, window.bounds.width, 'fills the window')
})

test('forces a theme', async (t) => {
  const canvas = new Canvas()

  await mount(t, canvas)

  let changes = 0

  canvas.on('actualThemeChanged', () => changes++)

  const other = canvas.actualTheme === ELEMENT_THEME.DARK ? ELEMENT_THEME.LIGHT : ELEMENT_THEME.DARK

  canvas.requestedTheme = other

  t.equal(canvas.requestedTheme, other, 'requested')
  t.equal(canvas.actualTheme, other, 'drawn in it')

  await afterAnimationFrame()

  t.equal(changes, 1, 'emitted')
})
