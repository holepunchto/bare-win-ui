# bare-win-ui

WinUI 3 for Bare on Windows. It gives you WinUI's elements in JavaScript, along with a runtime that starts the Windows App SDK for you, so a Bare app can have a native Windows window.

```
npm i bare-win-ui
```

## Usage

```js
const { Window, Canvas, TextBlock, SolidColorBrush } = require('bare-win-ui')

const window = new Window()

window.title = 'Hello'

const root = new Canvas()

root.background = new SolidColorBrush({ color: { r: 255, g: 255, b: 255 } })

const text = new TextBlock()

text.text = 'Click me'
text.fontSize = 32

root.children.append(text)

let clicks = 0

root.on('pointerPressed', () => {
  text.text = `Clicked ${++clicks} times`
})

window.content = root
window.activate()
```

Build the app with `bare-build` and this runtime:

```console
bare-build --host win32-x64 --runtime bare-win-ui/runtime --identifier com.example.Hello index.js
```

Lengths are in device independent pixels unless they say otherwise, and colours are `{ a, r, g, b }` objects with components from 0 to 255. Objects that have events, such as elements, text boxes and switches, emit them as ordinary events. WinUI is only asked to report an event while something listens to it.

## License

Apache-2.0
