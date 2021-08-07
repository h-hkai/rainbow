#include "../rainbow/rainbow.h"
#include <assert.h>

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void test_assert() {
    RAINBOW_LOG_INFO(g_logger) << rainbow::BacktraceToString(10, "    ", 2);
    RAINBOW_ASSERT2(0 == 1, "hahahahah");
}

int main(int argc, char *argv[]) {
    test_assert();
    return 0;
}
