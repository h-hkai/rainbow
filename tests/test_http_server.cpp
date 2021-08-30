#include "../rainbow/http/http_server.h"
#include "../rainbow/http/servlet.h"
#include "../rainbow/iomanager.h"
#include "../rainbow/log.h"

static rainbow::Logger::ptr g_logger = RAINBOW_LOG_ROOT();

void run() {
    rainbow::http::HttpServer::ptr server(new rainbow::http::HttpServer);
    rainbow::Address::ptr addr = rainbow::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while (!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/rainbow/xx", [](rainbow::http::HttpRequest::ptr req
                ,rainbow::http::HttpResponse::ptr rsp
                ,rainbow::http::HttpSession::ptr session) {
        rsp->setBody(req->toString());
        return 0;
    });

    sd->addGlobServlet("/rainbow/*", [](rainbow::http::HttpRequest::ptr req
                ,rainbow::http::HttpResponse::ptr rsp
                ,rainbow::http::HttpSession::ptr session) {
        rsp->setBody("Glob:\r\n" + req->toString());
        return 0;
    });
    server->start();
}

int main(int argc, char *argv[]) {
    rainbow::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
