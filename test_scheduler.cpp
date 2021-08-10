#include "rainbow/rainbow.h"

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

int main(int argc, char *argv[]) {
    rainbow::Scheduler sc;
    sc.stop();
    return 0;
}
