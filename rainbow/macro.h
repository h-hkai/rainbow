#ifndef __RAINBOW_MACRO_H__
#define __RAINBOW_MACRO_H__

#include <string.h>
#include <assert.h>

#include "util.h"

#define RAINBOW_ASSERT(x) \
    if (!(x)) { \
        RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << rainbow::BacktraceToString("    ", 100, 2); \
        assert(x); \
    }

#define RAINBOW_ASSERT2(x, w) \
    if (!(x)) { \
        RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" w \
            << rainbow::BacktraceToString("    ", 100, 2); \
        assert(x); \
    }


#endif 
