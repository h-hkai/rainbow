#include "../rainbow/rainbow.h"

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void run_in_fiber() {
    RAINBOW_LOG_INFO(g_logger) << "run_in_fiber begin";
    rainbow::Fiber::YieldToHold();
    RAINBOW_LOG_INFO(g_logger) << "run_in_fiber end";
    rainbow::Fiber::YieldToHold();
}

void test_fiber() {
    RAINBOW_LOG_INFO(g_logger) << "main after -1";
    {
        rainbow::Fiber::GetThis();
        RAINBOW_LOG_INFO(g_logger) << "main begin";
        rainbow::Fiber::ptr fiber(new rainbow::Fiber(run_in_fiber));
        fiber->swapIn();
        RAINBOW_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        RAINBOW_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    RAINBOW_LOG_INFO(g_logger) << "main after end2";

}

int main(int argc, char *argv[]) {
    rainbow::Thread::SetName("main");
    
    std::vector<rainbow::Thread::ptr> thrs;
    for (int i = 0; i < 3; ++i) {
        thrs.push_back(rainbow::Thread::ptr(new rainbow::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for (auto i : thrs) {
        i->join();
    }
    return 0;
}
