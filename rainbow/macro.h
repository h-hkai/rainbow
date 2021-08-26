#ifndef __RAINBOW_MACRO_H__
#define __RAINBOW_MACRO_H__

#include <string.h>
#include <assert.h>

#include "util.h"

#if defined __GNUC__ || defined __llvm__
#    define RAINBOW_LICKLY(x)           __builtin_expect(!!(x), 1)
#    define RAINBOW_UNLICKLY(x)         __builtin_expect(!!(x), 0)
#else
#    define RAINBOW_LICKLY(x)           (x)
#    define RAINBOW_UNLICKLY(x)         (x)
#endif

#define RAINBOW_ASSERT(x) \
    if (RAINBOW_UNLICKLY(!(x))) { \
        RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << rainbow::BacktraceToString("    ", 100, 2); \
        assert(x); \
    }

#define RAINBOW_ASSERT2(x, w) \
    if (RAINBOW_UNLICKLY(!(x))) { \
        RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" w \
            << rainbow::BacktraceToString("    ", 100, 2); \
        assert(x); \
    }


#endif 
