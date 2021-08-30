#include "../rainbow/tcp_server.h"
#include "../rainbow/log.h"
#include "../rainbow/iomanager.h"
#include "../rainbow/bytearray.h"
#include "../rainbow/socket.h"

static rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

class EchoServer : public rainbow::TcpServer {
public:
    EchoServer(int type);
    void handleClient(rainbow::Socket::ptr client);

private:
    int m_type = 0;
};

EchoServer::EchoServer(int type) 
    :m_type(type) {
}

void EchoServer::handleClient(rainbow::Socket::ptr client) {
    RAINBOW_LOG_INFO(g_logger) << "handleClient " << *client;
    rainbow::ByteArray::ptr ba(new rainbow::ByteArray);
    while (true) {
        ba->clear();
        std::vector<iovec> iovs;
        ba->getWriteBuffers(iovs, 1024);

        int rt = client->recv(&iovs[0], iovs.size());
        if (rt == 0) {
            RAINBOW_LOG_INFO(g_logger) << "client close: " << *client;
            break;
        } else if (rt < 0) {
            RAINBOW_LOG_INFO(g_logger) << "client error rt = " << rt
                << " errno = " << errno << " errstr = " << strerror(errno);
            break;
        }
        ba->setPosition(ba->getPosition() + rt);
        ba->setPosition(0);
        //RAINBOW_LOG_INFO(g_logger) << "recv rt = " << rt << " data = "
        //                        << std::string((char*)iovs[0].iov_base, rt);
        if (m_type == 1) { // text
            //RAINBOW_LOG_INFO(g_logger) << ba->toString();
            std::cout << ba->toString();
        } else {
            //RAINBOW_LOG_INFO(g_logger) << ba->toHexString();
            std::cout << ba->toHexString();
        }
        std::cout.flush();
    }
}

int type = 1;

void run() {
    EchoServer::ptr es(new EchoServer(type));
    auto addr = rainbow::Address::LookupAny("0.0.0.0:8020");
    while (!es->bind(addr)) {
        sleep(2);
    }
    es->start();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        RAINBOW_LOG_INFO(g_logger) << "used as[" << argv[0] 
                            << " -t] or [" << argv[0] << " -b]";
        return 0;
    }
    if (!strcmp(argv[1], "-b")) {
        type = 2;
    }
    rainbow::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
