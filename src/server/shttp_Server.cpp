
#include <spdlog/spdlog.h>

#include <http/respond.hpp>
#include <server/shttp_Server.hpp>

simpleHTTP::Server&
simpleHTTP::Server::start() {
  while (true) {
    size_t evCnt = srvSock.poll_wait();
    handleEvents(evCnt);
  }

  return *this;
}

void
simpleHTTP::Server::handleEvents(size_t eventCount) {
  for (size_t i = 0; i < eventCount; ++i) {
    epoll_data_t event = srvSock.getEvents(i);

    if (event.fd == srvSock.fd()) {
      srvSock.newConnection();
    } else {
      handleData(event.fd);
    }
  }
}

char buffer[2048];
void
simpleHTTP::Server::handleData(sock_fd sock) {
  int readCnt = read(sock, buffer, 2048);
  if (readCnt == 0) {
    srvSock.closeConnection(sock);
    return;
  }
  handleRequest(sock, buffer);
}

void
simpleHTTP::Server::handleRequest(sock_fd sock, const char* req) {
  auto route = Parsing::getRoute(req);
  if (!route) {
    Respond::BadRequest(sock);
    return;
  }

  auto content = pages.loadPage(route.value());
  if (!content) {
    Respond::NotFound(route.value(), sock);
    return;
  }

  Respond::WebPage(content.value(), sock);
  pages.contentUsed(content.value().file.content);
}