#include "../rainbow/uri.h"
#include <iostream>

int main(int argc, char *argv[]) {
    //rainbow::Uri::ptr uri = rainbow::Uri::Create("http://www.sylar.top/test/uri?id=100&name=rainbow#frg");
    rainbow::Uri::ptr uri = rainbow::Uri::Create("http://www.sylar.top");
    std::cout << uri->toString() << std::endl;
    std::cout << "--------------" << std::endl;
    auto addr = uri->createAddress();
    std::cout << *addr << std::endl;
    return 0;
}
