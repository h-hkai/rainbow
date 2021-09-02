#ifndef __RAINBOW_HTTP_HTTP_SERVER_H
#define __RAINBOW_HTTP_HTTP_SERVER_H

#include "http_session.h"
#include "servlet.h"
#include "../tcp_server.h"
#include "../iomanager.h"

namespace rainbow {
namespace http {

class HttpServer : public TcpServer {
public:
    typedef std::shared_ptr<HttpServer> ptr;
    HttpServer(bool keepalive = false
              ,rainbow::IOManager* worker = rainbow::IOManager::GetThis()
              ,rainbow::IOManager* accept_worker = rainbow::IOManager::GetThis());

    ServletDispatch::ptr getServletDispatch() const { return m_dispatch; }
    void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v; }
protected:
    virtual void handleClient(Socket::ptr client) override;

private:
    bool m_isKeepalive;
    ServletDispatch::ptr m_dispatch;
};

}
}


#endif /* ifndef __RAINBOW_HTTP_HTTP_SERVER_H */
