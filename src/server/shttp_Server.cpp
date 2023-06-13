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
#include "pages/page_content.hpp"

simple::Server& simple::Server::start() {
  while (true) {
    size_t evCnt = _srvSock.pollWait();
    handleEvents(evCnt);
  }

  return *this;
}

void simple::Server::handleEvents(size_t eventCount) {
  for (size_t i = 0; i < eventCount; ++i) {
    epoll_data_t event = _srvSock.getEvents(i);

    if (event.fd == _srvSock.fd()) {
      _srvSock.newConnection();
    } else {
      handleData(event.fd);
    }
  }
}

// NOLINTBEGIN - TODO: this will be updated with workers
char buffer[2048];
void simple::Server::handleData(sock_fd sock) {
  size_t readCnt = read(sock, buffer, 2048);
  if (readCnt == 0) {
    _srvSock.closeConnection(sock);
    return;
  }
  handleRequest(sock, buffer, readCnt);
}
// NOLINTEND

void simple::Server::handleRequest(sock_fd sock, const char* req, size_t size) {
  auto request = simple::http::parse(std::string_view(req, size));

  // parse request, get length, read length of bytes

  if (!request) {
    respond::badRequest(sock);
    return;
  }

  auto page = _pages.loadPage(request->getUri());
  respond::webPage(
      (page.found == LoadResult::SUCCESS ? http::Status::OK : http::Status::NOT_FOUND),
      page.content, sock);
}