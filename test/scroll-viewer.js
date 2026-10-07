const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const { Canvas, FrameworkElement, ScrollViewer } = require('..')
const { mount } = require('./helpers')

const { SCROLL_MODE, SCROLL_BAR_VISIBILITY } = ScrollViewer

function scrolling() {
  const viewer = new ScrollViewer()
  const content = new Canvas()

  content.width = 1000
  content.height = 2000
  content.horizontalAlignment = FrameworkElement.HORIZONTAL_ALIGNMENT.LEFT
  content.verticalAlignment = FrameworkElement.VERTICAL_ALIGNMENT.TOP

  viewer.horizontalScrollMode = SCROLL_MODE.ENABLED
  viewer.horizontalScrollBarVisibility = SCROLL_BAR_VISIBILITY.AUTO
  viewer.content = content

  return { viewer, content }
}

test('keeps the content wrapper', (t) => {
  const { viewer, content } = scrolling()

  t.ok(viewer.content === content, 'same wrapper')

  viewer.content = null

  t.equal(viewer.content, null, 'removed')
})

test('sets the scroll modes', (t) => {
  const viewer = new ScrollViewer()

  viewer.verticalScrollMode = SCROLL_MODE.DISABLED
  viewer.verticalScrollBarVisibility = SCROLL_BAR_VISIBILITY.HIDDEN

  t.equal(viewer.verticalScrollMode, SCROLL_MODE.DISABLED, 'mode')
  t.equal(viewer.verticalScrollBarVisibility, SCROLL_BAR_VISIBILITY.HIDDEN, 'visibility')
})

test('measures what there is to scroll', async (t) => {
  const { viewer } = scrolling()

  await mount(t, viewer)

  t.equal(viewer.extentWidth, 1000, 'extent width')
  t.equal(viewer.extentHeight, 2000, 'extent height')
  t.equal(viewer.viewportWidth, viewer.actualWidth, 'viewport width')
  t.equal(viewer.viewportHeight, viewer.actualHeight, 'viewport height')
  t.equal(viewer.scrollableHeight, 2000 - viewer.viewportHeight, 'scrollable height')
})

test('scrolls on the next layout pass', async (t) => {
  const { viewer } = scrolling()

  await mount(t, viewer)

  const events = []

  viewer.on('viewChanged', (event) => events.push(event))

  t.equal(viewer.changeView(null, 100, null, true), true, 'accepted')
  t.equal(viewer.verticalOffset, 0, 'not yet')

  viewer.updateLayout()

  t.equal(viewer.verticalOffset, 100, 'scrolled')
  t.equal(viewer.horizontalOffset, 0, 'only along the axis asked for')

  await afterAnimationFrame()

  t.ok(events.length > 0, 'emitted')
  t.equal(events[events.length - 1].isIntermediate, false, 'and settled')
})

test('clamps an offset to what there is to scroll', async (t) => {
  const { viewer } = scrolling()

  await mount(t, viewer)

  viewer.changeView(1e6, 1e6, null, true)
  viewer.updateLayout()

  t.equal(viewer.horizontalOffset, viewer.scrollableWidth, 'horizontal')
  t.equal(viewer.verticalOffset, viewer.scrollableHeight, 'vertical')
})
