#pragma once
#include <stddef.h>
/* Packaged macOS app: immutable assets stay in Resources; mutable files live
   in Application Support. Returns 1 if prepared, 0 for a development data dir. */
int re_bundle_prepare_data(const char *seed, char *out, size_t size);
