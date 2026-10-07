const { test } = require('bare-tap')
const { FontFamily, Run, SolidColorBrush, TextBlock } = require('..')
const text = require('../lib/text')

test('sets the text of a text block', (t) => {
  const block = new TextBlock()

  t.equal(block.text, '', 'empty')

  block.text = 'Grüße 👋'

  t.equal(block.text, 'Grüße 👋', 'round trips non-ASCII text')
})

test('sets how a text block lays out its text', (t) => {
  const block = new TextBlock()

  block.fontSize = 20
  block.lineHeight = 30
  block.maxLines = 2
  block.textAlignment = TextBlock.TEXT_ALIGNMENT.CENTER
  block.textWrapping = TextBlock.TEXT_WRAPPING.WRAP
  block.textTrimming = TextBlock.TEXT_TRIMMING.CHARACTER_ELLIPSIS

  t.equal(block.fontSize, 20, 'font size')
  t.equal(block.lineHeight, 30, 'line height')
  t.equal(block.maxLines, 2, 'lines')
  t.equal(block.textAlignment, TextBlock.TEXT_ALIGNMENT.CENTER, 'alignment')
  t.equal(block.textWrapping, TextBlock.TEXT_WRAPPING.WRAP, 'wrapping')
  t.equal(block.textTrimming, TextBlock.TEXT_TRIMMING.CHARACTER_ELLIPSIS, 'trimming')
})

test('wraps to the width it is given', (t) => {
  const block = new TextBlock()

  block.text = 'A string long enough to wrap onto more than one line when it is narrow'
  block.textWrapping = TextBlock.TEXT_WRAPPING.WRAP

  block.measure({ width: 1000, height: Infinity })

  const wide = block.desiredSize.height

  block.measure({ width: 100, height: Infinity })

  t.ok(block.desiredSize.height > wide)
})

test('keeps the font family and brush wrappers', (t) => {
  const block = new TextBlock()
  const family = new FontFamily({ familyName: 'Consolas' })
  const brush = new SolidColorBrush()

  t.equal(family.source, 'Consolas', 'the family name')

  block.fontFamily = family
  block.foreground = brush

  t.ok(block.fontFamily === family, 'same family wrapper')
  t.ok(block.foreground === brush, 'same brush wrapper')
})

test('shows runs of styled text', (t) => {
  const block = new TextBlock()
  const run = new Run()

  run.text = 'Bold'
  run.fontSize = 18
  run.fontWeight = 700
  run.fontStyle = Run.FONT_STYLE.ITALIC
  run.characterSpacing = 100
  run.textDecorations = Run.TEXT_DECORATIONS.UNDERLINE

  t.equal(run.text, 'Bold', 'text')
  t.equal(run.fontSize, 18, 'font size')
  t.equal(run.fontWeight, 700, 'weight')
  t.equal(run.fontStyle, Run.FONT_STYLE.ITALIC, 'style')
  t.equal(run.characterSpacing, 100, 'spacing')

  block.inlines.append(run)

  t.equal(block.inlines.size, 1, 'one run')
  t.equal(block.text, 'Bold', 'the text of the runs')

  block.inlines.clear()

  t.equal(block.inlines.size, 0, 'cleared')
})

test('sets the colour of a brush', (t) => {
  const brush = new SolidColorBrush({ color: { r: 10, g: 20, b: 30 } })

  t.deepStrictEqual(brush.color, { a: 255, r: 10, g: 20, b: 30 }, 'opaque by default')

  brush.color = { a: 128, b: 255 }

  t.deepStrictEqual(brush.color, { a: 128, r: 0, g: 0, b: 255 }, 'left out is 0')
})

test('measures text', (t) => {
  const short = text.measure('Hello')
  const long = text.measure('Hello, world')

  t.ok(short.width > 0 && short.height > 0, 'has a size')
  t.equal(short.lines, 1, 'one line')
  t.ok(long.width > short.width, 'wider when longer')
  t.ok(text.measure('Hello, world', {}, long.width / 2).lines > 1, 'wraps')
  t.ok(text.measure('Hello', { size: 40 }).height > short.height, 'taller when larger')
})
