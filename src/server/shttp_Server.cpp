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

#include "server/shttp_Server.hpp"
#include <new>
#include "http/respond.hpp"
#include "logging/logging.hpp"
#include "pages/page_content.hpp"
#include "server/events.hpp"

auto simple::Server::start() -> simple::Server& {
  _eventHandler.on<event::Message>([&](event::Message message) {
    debug("Event Handler");
    handleRequest(message.sock_fd, message.message, message.readCnt);
    delete[] message.message;
  });

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
      auto [message, length] = readMessage(event.fd);
      if (message)
        _eventHandler.emit<event::Message>({event.fd, message, length});
      else
        _srvSock.closeConnection(event.fd);
    }
  }
}

void simple::Server::handleRequest(sock_fd sock, const char* req, size_t size) {
  debug("New Request");
  auto request = simple::http::Parser().parse(std::string_view(req, size));

  // parse request, get length, read length of bytes

  if (!request) {
    debug("Bad Request");
    respond::badRequest(sock);
    return;
  }

  auto page = _pages.loadPage(request->getUri().uri);
  respond::webPage((page.found == LoadResult::SUCCESS ? http::Status::OK : http::Status::NOT_FOUND),
                   page.content, sock);
}

auto simple::Server::readMessage(sock_fd sock) -> std::pair<char*, size_t> {
  auto*  data = new char[READ_SZ];
  size_t readCnt = read(sock, data, READ_SZ);
  if (readCnt == 0) {
    delete[] data;
    return {nullptr, 0};
  }

  return {data, readCnt};
}