#include "../rainbow/http/http.h"
#include "../rainbow/log.h"

void test_request() {
    rainbow::http::HttpRequest::ptr req(new rainbow::http::HttpRequest);
    req->setHeader("host", "www.baidu.com");
    req->setBody("hello rainbow");

    req->dump(std::cout) << std::endl;
}

void test_response() {
    rainbow::http::HttpResponse::ptr rsp(new rainbow::http::HttpResponse);
    rsp->setHeader("X-X", "rainbow");
    rsp->setBody("hello rainbow");
    rsp->setStatus((rainbow::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}

int main(int argc, char *argv[]) {
    test_request();
    test_response();
    return 0;
}
