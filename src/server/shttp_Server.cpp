/**
 * @file shttp_Server.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

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

  auto page = pages.loadPage(route.value());
  Respond::WebPage((page.found ? Status::OK : Status::NOT_FOUND), page.content, sock);
}