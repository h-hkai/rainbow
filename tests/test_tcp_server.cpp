#include "../rainbow/tcp_server.h"
#include "../rainbow/iomanager.h"
#include "../rainbow/log.h"

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void run() {
    auto addr = rainbow::Address::LookupAny("0.0.0.0:8033");
    //auto addr2 = rainbow::UnixAddress::ptr(new rainbow::UnixAddress("/tmp/unix_addr"));
    //RAINBOW_LOG_INFO(g_logger) << *addr << " - " << *addr2;
    std::vector<rainbow::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    rainbow::TcpServer::ptr tcp_server(new rainbow::TcpServer);
    std::vector<rainbow::Address::ptr> fails;
    while (!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
}

int main(int argc, char *argv[]) {
    rainbow::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
