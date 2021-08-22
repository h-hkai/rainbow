#include "../rainbow/rainbow.h"
#include "../rainbow/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>

rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void test_fiber() {
    RAINBOW_LOG_INFO(g_logger) << "test_fiber";

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "220.181.38.148", &addr.sin_addr.s_addr);

    if (!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {

    } else if (errno == EINPROGRESS) {
        RAINBOW_LOG_INFO(g_logger) << "add event errno = " << errno << " " << strerror(errno);

        rainbow::IOManager::GetThis()->addEvent(sock, rainbow::IOManager::READ, [](){
            RAINBOW_LOG_INFO(g_logger) << "read callback";
        });
        
        rainbow::IOManager::GetThis()->addEvent(sock, rainbow::IOManager::WRITE, [sock](){
            RAINBOW_LOG_INFO(g_logger) << "write callback";
            //close(sock);
            rainbow::IOManager::GetThis()->cancelEvent(sock, rainbow::IOManager::READ);
            close(sock);
        });
    } else {
        RAINBOW_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
    }

}

void test1() {
    std::cout << "EPOLLIN = " << EPOLLIN
              << " EPOLLOUT = " << EPOLLOUT << std::endl;

    rainbow::IOManager iom(2, false);
    iom.schedule(&test_fiber);
}

rainbow::Timer::ptr s_timer;
void test_timer() {
    rainbow::IOManager iom(2);
     s_timer = iom.addTimer(1000, [](){
        static int i = 0;
        RAINBOW_LOG_INFO(g_logger) << "hello timer i = " << i;
        if (++i == 5) {
            s_timer->reset(2000, true);
            //s_timer->cancel();
        }
    }, true);
}

int main(int argc, char *argv[]) {
    //test1();
    test_timer();
    return 0;
}
