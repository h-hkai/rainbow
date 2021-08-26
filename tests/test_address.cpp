#include "../rainbow/address.h"
#include "../rainbow/log.h"

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void test() {
    std::vector<rainbow::Address::ptr> addrs;

    RAINBOW_LOG_INFO(g_logger) << "begin";
    bool v = rainbow::Address::Lookup(addrs, "www.baidu.com");
    RAINBOW_LOG_INFO(g_logger) << "end";

    if (!v) {
        RAINBOW_LOG_ERROR(g_logger) << "lookup fail";
        return ;
    }

    for (size_t i = 0; i < addrs.size(); ++i) {
        RAINBOW_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<rainbow::Address::ptr, uint32_t>> results;

    bool v = rainbow::Address::GetInterfaceAddresses(results);
    if (!v) {
        RAINBOW_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return ;
    }

    for (auto& i : results) {
        RAINBOW_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() 
            << " - " << i.second.second;
    }
}

void test_ipv4() {
    auto addr = rainbow::IPAddress::Create("www.baidu.com");
    if (addr) {
        RAINBOW_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char *argv[]) {
    //test();
    //test_iface();
    test_ipv4();
    return 0;
}
