/**
 * @file shttp_Server.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 *
 * @copyright Copyright 2023 Rolland Goodenough
 *
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_SERVER_HPP
#define SIMPLE_HTTP_SERVER_HPP

#include <csignal>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "party_llama/event_system_async.hpp"

#include "events.hpp"
#include "http/parsing.hpp"
#include "pages/page_manager.hpp"
#include "server/server.types.hpp"
#include "socket/socket.hpp"
#include "types/data.types.hpp"

namespace simple {

constexpr port DEFAULT_PORT = 9000;

class ServerException : public std::runtime_error {
 public:
  explicit ServerException(const std::string& message) : std::runtime_error(message) {}
  static void error(const std::string& message) { throw ServerException(message); }
};

class Server {
 public:
  Server(int srvSock) : _srvSock(srvSock) {}

  auto start() -> Server&;

 private:
  Socket _srvSock;
  Pages  _pages;

  pllama::EventSystem_Async<event::Message> _eventHandler;

  static constexpr size_t READ_SZ = 2048;

  void handleEvents(size_t);
  void handleData(sock_fd);
  void handleRequest(sock_fd, const char*, size_t);

  [[nodiscard]] static auto readMessage(sock_fd) -> std::pair<char*, size_t>;

 public:
  Server() : _srvSock(DEFAULT_PORT) {}
  ~Server() = default;

  Server(Server&&) noexcept = delete;
  auto operator=(Server&&) noexcept -> Server& = delete;
  Server(const Server&) = delete;
  auto operator=(const Server&) -> Server& = delete;
};
}  // namespace simple

#endif