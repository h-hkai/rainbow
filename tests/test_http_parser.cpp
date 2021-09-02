#include "../rainbow/http/http_parser.h"
#include "../rainbow/log.h"

static rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

const char test_request_data[] = "POST / HTTP/1.1\r\n"
                                 "Host: www.sylar.top\r\n"
                                 "Content-Length: 10\r\n\r\n"
                                 "1234567890";

void test_request() {
    rainbow::http::HttpRequestParser parser;
    std::string tmp = test_request_data;
    size_t s = parser.execute(&tmp[0], tmp.size());
    RAINBOW_LOG_ERROR(g_logger) << "execute rt = " << s
        << " has_error = " << parser.hasError()
        << " is_finished = " << parser.isFinished()
        << " total = " << tmp.size()
        << " content_length = " << parser.getContentLength();

    tmp.resize(tmp.size() - s);
    RAINBOW_LOG_INFO(g_logger) << parser.getData()->toString();
    RAINBOW_LOG_INFO(g_logger) << tmp;
}

const char test_response_data[] = "HTTP/1.1 200 OK"
        "Server: nginx/1.14.0 (Ubuntu)\r\n"
        "Date: Sun, 29 Aug 2021 03:21:36 GMT\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 612\r\n"
        "Last-Modified: Mon, 16 Aug 2021 04:46:17 GMT\r\n"
        "Connection: close\r\n"
        "ETag: \"6119ed99-264\"\r\n"
        "Accept-Ranges: bytes\r\n"
        "<!DOCTYPE html>\r\n"
        "<html>\r\n"
        "<body>\r\n"
        "<h1>Welcome to nginx!</h1>\r\n"
        "</body>\r\n"
        "</html>\r\n";

void test_response() {
    rainbow::http::HttpResponseParser parser;
    std::string tmp = test_response_data;
    size_t s = parser.execute(&tmp[0], tmp.size(), true);
    RAINBOW_LOG_ERROR(g_logger) << "execute rt = " << s
        << " has_error = " << parser.hasError()
        << " is_finished = " << parser.isFinished()
        << " total = " << tmp.size()
        << " content_length = " << parser.getContentLength()
        << " tmp[s] = " << tmp[s];

    tmp.resize(tmp.size() - s);

    RAINBOW_LOG_INFO(g_logger) << parser.getData()->toString();
    RAINBOW_LOG_INFO(g_logger) << tmp;
}

int main(int argc, char *argv[]) {
    test_request();
    RAINBOW_LOG_INFO(g_logger) << "------------------";
    test_response();
    return 0;
}
