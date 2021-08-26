#include "../rainbow/socket.h"
#include "../rainbow/rainbow.h"
#include "../rainbow/iomanager.h"

static rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void test_socket() {
    rainbow::IPAddress::ptr addr = rainbow::Address::LookupAnyIPAddress("www.baidu.com");
    if (addr) {
        RAINBOW_LOG_INFO(g_logger) << "get address: " << addr->toString();
    } else {
        RAINBOW_LOG_ERROR(g_logger) << "get address fail";
        return ;
    }
    
    rainbow::Socket::ptr sock = rainbow::Socket::CreateTCP(addr);
    addr->setPort(80);
    RAINBOW_LOG_INFO(g_logger) << "addr = " << addr->toString();
    if (!sock->connect(addr)) {
        RAINBOW_LOG_ERROR(g_logger) << "connect " << addr->toString() << " fail";
        return;
    } else {
        RAINBOW_LOG_INFO(g_logger) << "connect " << addr->toString() << " connected";
    }

    const char buff[] = "GET / HTTP/1.0\r\n\r\n";

    int rt = sock->send(buff, sizeof(buff));
    if (rt <= 0) {
        RAINBOW_LOG_INFO(g_logger) << "send fail rt = " << rt;
        return;
    }

    std::string buffs;
    buffs.resize(4096);
    rt = sock->recv(&buffs[0], buffs.size());

    if (rt <= 0) {
        RAINBOW_LOG_INFO(g_logger) << "recv fail rt = " << rt;
        return;
    }

    buffs.resize(rt);
    RAINBOW_LOG_INFO(g_logger) << buffs;
}

int main(int argc, char *argv[]) {
    rainbow::IOManager iom;
    iom.schedule(&test_socket);
    return 0;
}
