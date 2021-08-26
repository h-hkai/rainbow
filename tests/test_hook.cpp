#include "../rainbow/hook.h"
#include "../rainbow/log.h"
#include "../rainbow/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

rainbow::Logger::ptr g_logger2 = RAINBOW_LOG_ROOT();

void test_sleep() {
    rainbow::IOManager iom(1);
    iom.schedule([](){
        sleep(2);
        RAINBOW_LOG_INFO(g_logger2) << "sleep 2";
    });
    iom.schedule([](){
        sleep(3);
        RAINBOW_LOG_INFO(g_logger2) << "sleep 3";
    });
    RAINBOW_LOG_INFO(g_logger2) << "test_sleep";
}

void test_sock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "220.181.38.148", &addr.sin_addr.s_addr);

    RAINBOW_LOG_INFO(g_logger2) << "begin connect";
    int rt = connect(sock, (const sockaddr*)&addr, sizeof(addr));
    RAINBOW_LOG_INFO(g_logger2) << "connect rt = " << rt << " error = " << errno;

    if (rt) {
        return;
    }

    const char data[] = "GET / HTTP/1.0\r\n\r\n";
    rt = send(sock, data, sizeof(data), 0);
    RAINBOW_LOG_INFO(g_logger2) << "send rt = " << rt << " errno = " << errno;

    if (rt <= 0) {
        return;
    }

    std::string buff;
    buff.resize(4096);

    rt = recv(sock, &buff[0], buff.size(), 0);
    RAINBOW_LOG_INFO(g_logger2) << "recv rt = " << rt << " errno = " << errno;

    if (rt <= 0) {
        return;
    }

    buff.resize(rt);
    RAINBOW_LOG_INFO(g_logger2) << buff;
}

int main(int argc, char *argv[]) {
    //test_sleep();
    //test_sock();
    rainbow::IOManager iom;
    iom.schedule(test_sock);
    return 0;
}
