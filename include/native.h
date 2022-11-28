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

extern void (*native_callback) (char *data);

void init_native_callback (void (*callback) (char *data));
void va_cb_native         (const char *format, va_list ap);
void cb_native            (const char *format, ...);

hashcat_ctx_t *build_hashcat_ctx ();
void           free_hashcat_ctx  (hashcat_ctx_t *hashcat_ctx);

#endif //HASHCAT_MOBILE_NATIVE_H
