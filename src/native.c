/**
 * Author......: See docs/credits.txt
 * License.....: MIT
 */

#include "native.h"

/**
 * Stores the native callback function. MUST call `init_native_callback` first.
 *
 * @param data the char array to pass back to native
 */
void (*native_callback) (char *data);

/**
 * Initialize `native_callback`. This is used to allow native callbacks to other code.
 * Instead of outputs being routed to the console.
 * When compiling, set NATIVE_CB flag.
 *
 * @param callback the function that will be called back to native code.
 */
void init_native_callback (void (*callback) (char *data))
{
  native_callback = callback;
}

void va_cb_native (const char *format, va_list ap)
{
  char *data;
  int size = vasprintf (&data, format, ap);

  if (size != -1) {
    native_callback (data);
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
