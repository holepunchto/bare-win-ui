# bare-win-ui

WinUI bindings and runtime for Bare.

```
npm i bare-win-ui
```

## WebView developer tools

`webView.devToolsEnabled` gets or sets WebView2's `AreDevToolsEnabled` setting,
which controls opening DevTools through the context menu and keyboard shortcuts.
The default is `true`. Values assigned before WebView2 is ready are retained and
applied during initialization. Use `webView.openDevToolsWindow()` to open DevTools
programmatically.

## License

Apache-2.0
