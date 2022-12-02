/**
 * Author......: See docs/credits.txt
 * License.....: MIT
 */

#ifndef HASHCAT_MOBILE_NATIVE_H
#define HASHCAT_MOBILE_NATIVE_H

#include <stdarg.h>
#include <stdlib.h>

#include "types.h"
#include "memory.h"
#include "dart_api_dl.h"

static Dart_Port_DL dart_port;

void init_native_callback (Dart_Port_DL port);
void va_cb_native         (const char *format, va_list ap);
void cb_native            (const char *format, ...);

hashcat_ctx_t *build_hashcat_ctx ();
void           free_hashcat_ctx  (hashcat_ctx_t *hashcat_ctx);

#endif //HASHCAT_MOBILE_NATIVE_H
