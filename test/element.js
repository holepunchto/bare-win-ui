const { test } = require('bare-tap')
const { Canvas, FrameworkElement, TextBlock } = require('..')
const { mount } = require('./helpers')

const { HORIZONTAL_ALIGNMENT, VERTICAL_ALIGNMENT, ELEMENT_THEME } = FrameworkElement

test('builds a hierarchy', (t) => {
  const parent = new Canvas()
  const a = new TextBlock()
  const b = new TextBlock()
  const c = new TextBlock()

  t.equal(a.parent, null, 'no parent')
  t.equal(parent.children.size, 0, 'no children')

  parent.children.append(a)
  parent.children.append(c)
  parent.children.insertAt(1, b)

  t.ok(a.parent === parent, 'same parent wrapper')
  t.equal(parent.children.size, 3, 'three children')
  t.ok(parent.children.getAt(1) === b, 'inserted')
  t.equal(parent.children.indexOf(c), 2, 'index')

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
  t.deepStrictEqual(transform.inverse.transformPoint(15, 25), { x: 5, y: 5 }, 'and back')
  t.deepStrictEqual(
    transform.transformBounds(0, 0, 30, 40),
    { x: 10, y: 20, width: 30, height: 40 },
    'bounds'
  )
})

test('lays out now when asked', async (t) => {
  const canvas = new Canvas()
  const child = new Canvas()

  canvas.children.append(child)

  await mount(t, canvas)

  child.width = 50
  child.height = 60

  t.equal(child.actualWidth, 0, 'not before the next pass')

  child.updateLayout()

  t.equal(child.actualWidth, 50, 'width')
  t.equal(child.actualHeight, 60, 'height')
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
  t.equal(changes, 1, 'emitted')
})
