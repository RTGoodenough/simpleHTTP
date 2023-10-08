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
#include "http/respond.hpp"
#include "logging/logging.hpp"
#include "pages/page_content.hpp"
#include "pirate.hpp"
#include "server/events.hpp"
#include "types/arg_types.hpp"

auto simple::Server::start() -> simple::Server& {
  _eventHandler.on<event::Message>([&](const event::Message& message) {
    debug("Event Handler");
    handle_request(message.sock_fd, message.message, message.readCnt);
  });

  while (true) {
    size_t evCnt = _srvSock.poll_wait();
    handle_events(evCnt);
  }

  return *this;
}

void simple::Server::handle_events(size_t eventCount) {
  for (size_t i = 0; i < eventCount; ++i) {
    epoll_data_t event = _srvSock.get_events(i);

    if (event.fd == _srvSock.fd()) {
      _srvSock.new_connection();
    } else {
      auto [message, length] = read_message(event.fd);
      if (!message.empty())
        _eventHandler.emit<event::Message>({event.fd, std::move(message), length});
      else
        _srvSock.close_connection(event.fd);
    }
  }
}

void simple::Server::handle_request(sock_fd sock, const std::vector<char>& req, size_t size) {
  debug("New Request");
  auto request = simple::http::Parser().parse(std::string_view(req.data(), size));

  if (!request) {
    debug("Bad Request");
    respond::badRequest(sock);
    return;
  }

  auto page = _pages.load_page(request->getUri().uri);
  respond::webPage((page.found == LoadResult::SUCCESS ? http::Status::OK : http::Status::NOT_FOUND),
                   page.content, sock);
}

auto simple::Server::read_message(sock_fd sock) -> std::pair<std::vector<char>, size_t> {
  auto   data = std::vector<char>(READ_SZ);
  size_t readCnt = read(sock, data.data(), READ_SZ);
  if (readCnt == 0) {
    return {{}, 0};
  }

  return {std::move(data), readCnt};
}

void simple::Server::setup_args() {
  pirate::Args::register_arg("port", pirate::ArgType::REQUIRED | pirate::ArgType::VALUE_REQUIRED);
  pirate::Args::register_arg("routes", pirate::ArgType::REQUIRED | pirate::ArgType::VALUE_REQUIRED);
  pirate::Args::register_arg("threads", pirate::ArgType::OPTIONAL | pirate::ArgType::VALUE_REQUIRED);
}