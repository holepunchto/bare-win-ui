// URIs and documents are handed on to Windows APIs that take C strings, where a
// NUL would cut them short and name something else.
exports.validateNoNullBytes = function validateNoNullBytes(value, name) {
  if (typeof value === 'string' && value.includes('\0')) {
    throw new TypeError(`The "${name}" argument must not contain null bytes`)
  }
}
