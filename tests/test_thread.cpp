#include "../rainbow/rainbow.h"
#include <unistd.h>

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

int count = 0;
//rainbow::RWMutex s_mutex;
rainbow::Mutex s_mutex;

void fun1() {
    RAINBOW_LOG_INFO(g_logger) << "name: " << rainbow::Thread::GetName()
                               << " this.name: " << rainbow::Thread::GetThis()->getName()
                               << " id: " << rainbow::GetThreadId()
                               << " this.id: " << rainbow::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        //rainbow::RWMutex::WriteLock lock(s_mutex);
        rainbow::Mutex::Lock lock(s_mutex);
        ++count;
    }
    
}

void fun2() {
    while(true) {
        RAINBOW_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        RAINBOW_LOG_INFO(g_logger) << "========================";
    }
}

int main(int argc, char** argv) {
    RAINBOW_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/zhangyu/rainbow/bin/conf/log2.yml");
    rainbow::Config::LoadFromYaml(root);
 
    std::vector<rainbow::Thread::ptr> thrs;

    for (int i = 0; i < 2; ++i) {
        rainbow::Thread::ptr thr(new rainbow::Thread(&fun2, "name_" + std::to_string(i * 2)));
        rainbow::Thread::ptr thr2(new rainbow::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }

    //sleep(20);

    for (size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }

    RAINBOW_LOG_INFO(g_logger) << "thread test end";
    RAINBOW_LOG_INFO(g_logger) << "count = " << count;

    return 0;
}
