const { afterAnimationFrame } = require('bare-animation-frame')
const { Window } = require('..')

// Closing the last window shuts the app down, so the tests share one that
// stays open and swap its content.
let window = null

exports.mount = async function mount(t, content) {
  if (window === null) {
    window = new Window()
    window.resizeClient(400, 300)
    window.activate()
  }

  window.content = content

  t.teardown(() => {
    window.content = null
  })

  // XAML only lays out and draws new content on its next frame.
  await afterAnimationFrame()

  return window
}
