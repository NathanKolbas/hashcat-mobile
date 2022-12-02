/**
 * Author......: See docs/credits.txt
 * License.....: MIT
 */

#include "native.h"

// Check this gist for setting up native callback for dart:
// https://gist.github.com/espresso3389/be5674ab4e3154f0b7c43715dcef3d8d

/**
 * Stores the native callback port. MUST call `init_native_callback` first.
 */
static Dart_Port_DL dart_port = 0;

/**
 * Initialize `native_callback`. This is used to allow native callbacks to other code.
 * Instead of outputs being routed to the console.
 * When compiling, set NATIVE_CB flag.
 *
 * @param callback the function that will be called back to native code.
 */
void init_native_callback (Dart_Port_DL port)
{
  dart_port = port;
}

void va_cb_native (const char *format, va_list ap)
{
  char *data;
  int size = vasprintf (&data, format, ap);

  if (size != -1) {
    if (!dart_port)
      return;
    Dart_CObject msg;
    msg.type = Dart_CObject_kString;
    msg.value.as_string = (char *)data;
    // The function is thread-safe; you can call it anywhere on your C++ code
    Dart_PostCObject_DL(dart_port, &msg);
  }

  free (data);
}

void cb_native (const char *format, ...)
{
  va_list args;
  va_start (args, format);
  va_cb_native (format, args);
  va_end (args);
}

hashcat_ctx_t *build_hashcat_ctx ()
{
  return (hashcat_ctx_t *) hcmalloc (sizeof (hashcat_ctx_t));
}

void free_hashcat_ctx (hashcat_ctx_t *hashcat_ctx)
{
  hcfree (hashcat_ctx);
}
