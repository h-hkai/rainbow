#include <iostream>

#include "../rainbow/http/http_connection.h"
#include "../rainbow/log.h"
#include "../rainbow/iomanager.h"

static rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void test_pool() {
    rainbow::http::HttpConnectionPool::ptr pool(new rainbow::http::HttpConnectionPool(
                "www.sylar.top", "", 80, 10, 1000 * 30, 5));
    rainbow::IOManager::GetThis()->addTimer(1000, [pool](){
            auto r = pool->doGet("/", 300);
            RAINBOW_LOG_INFO(g_logger) << r->toString();
    }, true);
}

void run() {
    rainbow::Address::ptr addr = rainbow::Address::LookupAnyIPAddress("www.sylar.top:80");
    if (!addr) {
        RAINBOW_LOG_INFO(g_logger) << "get addr error";
        return ;
    }

    rainbow::Socket::ptr sock = rainbow::Socket::CreateTCP(addr);
    bool rt = sock->connect(addr);

    if (!rt) {
        RAINBOW_LOG_INFO(g_logger) << "connect " << *addr << " failed";
        return ;
    }

    rainbow::http::HttpConnection::ptr conn(new rainbow::http::HttpConnection(sock));
    rainbow::http::HttpRequest::ptr req(new rainbow::http::HttpRequest);
    req->setPath("/blog/");
    req->setHeader("host", "www.sylar.top");

    RAINBOW_LOG_INFO(g_logger) << "req: " << std::endl << *req;

    conn->sendRequest(req);
    auto rsp = conn->recvResponse();

    if (!rsp) {
        RAINBOW_LOG_INFO(g_logger) << "recv response error";
        return ;
    }

    RAINBOW_LOG_INFO(g_logger) << "rsp:" << std::endl << *rsp;

    std::ofstream ofs("rsp.dat");
    ofs << *rsp;

    RAINBOW_LOG_INFO(g_logger) << "=====================";

    auto rt2 = rainbow::http::HttpConnection::DoGet("http://www.sylar.top/blog/", 300);
    RAINBOW_LOG_INFO(g_logger) << "result = " << rt2->result
        << " error = " << rt2->error
        << " rsp = " << (rt2->response ? rt2->response->toString() : "");

    RAINBOW_LOG_INFO(g_logger) << "=====================";
    test_pool();
}

int main(int argc, char *argv[]) {
    rainbow::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
