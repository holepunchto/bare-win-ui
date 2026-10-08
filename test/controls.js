const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const {
  Canvas,
  Control,
  PasswordBox,
  ProgressRing,
  SolidColorBrush,
  TextBox,
  ToggleSwitch
} = require('..')
const FocusManager = require('../lib/focus-manager')
const { mount } = require('./helpers')

test('sets the text of a text box', (t) => {
  const box = new TextBox()

  t.equal(box.text, '', 'empty')

  box.text = 'Grüße 👋'

  t.equal(box.text, 'Grüße 👋', 'round trips non-ASCII text')
})

test('emits when the text of a text box changes', async (t) => {
  const box = new TextBox()

  await mount(t, box)

  let changes = 0

  box.on('textChanged', () => changes++)
  box.text = 'Hello'

  await afterAnimationFrame()

  t.equal(changes, 1)
})

test('selects text in a text box', (t) => {
  const box = new TextBox()

  box.text = 'Hello'
  box.selectionStart = 1
  box.selectionLength = 2

  t.equal(box.selectionStart, 1, 'start')
  t.equal(box.selectionLength, 2, 'length')
})

test('sets the hints of a text box', (t) => {
  const box = new TextBox()

  t.equal(box.isReadOnly, false, 'writable')
  t.equal(box.acceptsReturn, false, 'one line')
  t.equal(box.placeholderText, '', 'no placeholder')

  box.isReadOnly = true
  box.acceptsReturn = true
  box.isSpellCheckEnabled = false
  box.placeholderText = 'Email'
  box.textWrapping = TextBox.TEXT_WRAPPING.WRAP
  box.textAlignment = TextBox.TEXT_ALIGNMENT.RIGHT
  box.inputScope = TextBox.INPUT_SCOPE_NAME_VALUE.EMAIL_SMTP_ADDRESS

  t.equal(box.isReadOnly, true, 'read only')
  t.equal(box.acceptsReturn, true, 'several lines')
  t.equal(box.isSpellCheckEnabled, false, 'no spell checking')
  t.equal(box.placeholderText, 'Email', 'placeholder')
  t.equal(box.textWrapping, TextBox.TEXT_WRAPPING.WRAP, 'wrapping')
  t.equal(box.textAlignment, TextBox.TEXT_ALIGNMENT.RIGHT, 'alignment')
})

test('reports focus moving between text boxes', async (t) => {
  const canvas = new Canvas()
  const a = new TextBox()
  const b = new TextBox()

  Canvas.setTop(b, 50)

  canvas.children.append(a)
  canvas.children.append(b)

  await mount(t, canvas)

  const events = []

  a.on('gotFocus', () => events.push('gotFocus'))
  a.on('lostFocus', () => events.push('lostFocus'))

  t.equal(a.focus(Control.FOCUS_STATE.PROGRAMMATIC), true, 'took the focus')

  await afterAnimationFrame()

  t.equal(FocusManager.tryMoveFocus(a, FocusManager.FOCUS_NAVIGATION_DIRECTION.NEXT), true, 'moved')

  await afterAnimationFrame()

  t.deepStrictEqual(events, ['gotFocus', 'lostFocus'])
})

test('sets the password of a password box', (t) => {
  const box = new PasswordBox()

  box.password = 'secret'
  box.placeholderText = 'Password'
  box.passwordRevealMode = PasswordBox.PASSWORD_REVEAL_MODE.HIDDEN

  t.equal(box.password, 'secret', 'password')
  t.equal(box.placeholderText, 'Password', 'placeholder')
})

test('emits when a toggle switch is toggled', async (t) => {
  const toggle = new ToggleSwitch()

  await mount(t, toggle)

  let changes = 0

  toggle.on('toggled', () => changes++)

  t.equal(toggle.isOn, false, 'off')

  toggle.isOn = true

  await afterAnimationFrame()

  t.equal(toggle.isOn, true, 'on')
  t.equal(changes, 1, 'emitted for a change from code')
})

test('disables a control', (t) => {
  const toggle = new ToggleSwitch()

  t.equal(toggle.isEnabled, true, 'enabled')

  toggle.isEnabled = false

  t.equal(toggle.isEnabled, false, 'disabled')
})

test('finds a part of the control template once loaded', async (t) => {
  const toggle = new ToggleSwitch()

  await mount(t, toggle)

  t.ok(toggle.templateChild('SwitchKnob') !== null, 'a part')
  t.equal(toggle.templateChild('NoSuchPart'), null, 'no part')
})

test('sets the brushes of a control', (t) => {
  const box = new TextBox()
  const brush = new SolidColorBrush({ color: { r: 255 } })

  box.background = brush
  box.foreground = brush
  box.borderBrush = brush

  t.ok(box.background === brush, 'same background wrapper')
  t.ok(box.foreground === brush, 'same foreground wrapper')
  t.ok(box.borderBrush === brush, 'same border wrapper')

  box.background = null

  t.equal(box.background, null, 'cleared')
})

test('spins a progress ring', (t) => {
  const ring = new ProgressRing()

  t.equal(ring.isActive, true, 'active')

  ring.isActive = false

  t.equal(ring.isActive, false, 'inactive')
})
