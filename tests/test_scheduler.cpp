#include "../rainbow/rainbow.h"

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void test_fiber()
{
    RAINBOW_LOG_INFO(g_logger) << "test in fiber";
    static int s_count = 5;
    sleep(1);
    if (--s_count >= 0) {
        rainbow::Scheduler::GetThis()->schedule(&test_fiber, rainbow::GetThreadId());
    }
}

int main(int argc, char *argv[]) {
    RAINBOW_LOG_INFO(g_logger) << "main";
    rainbow::Scheduler sc(3, false, "test");
    RAINBOW_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.start();
    sc.stop();
    RAINBOW_LOG_INFO(g_logger) << "over";
    return 0;
}

