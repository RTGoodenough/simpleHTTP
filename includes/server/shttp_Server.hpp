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

#include <party_llama/party_llama.hpp>

#include "events.hpp"
#include "http/parsing.hpp"
#include "pages/page_manager.hpp"
#include "pirate.hpp"
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
  explicit Server(pirate::Args& args) : _srvSock(std::stoi(args.get("port"))) {
    _pages.set_path(args.get("routes"));
    if (args.has("threads"))
      _eventHandler.set_threads(std::stoi(args.get("threads")));
    else
      _eventHandler.set_threads(1);
  }

  static void setup_args();

  auto start() -> Server&;

 private:
  Socket _srvSock;
  Pages  _pages;

  pllama::EventSystem_Async<event::Message> _eventHandler;

  static constexpr size_t READ_SZ = 2048;

  void handle_events(size_t);
  void handle_data(sock_fd);
  void handle_request(sock_fd, const char*, size_t);

  [[nodiscard]] static auto read_message(sock_fd) -> std::pair<char*, size_t>;

 public:
  Server() = delete;
  ~Server() = default;
  Server(Server&&) noexcept = delete;
  auto operator=(Server&&) noexcept -> Server& = delete;
  Server(const Server&) = delete;
  auto operator=(const Server&) -> Server& = delete;
};
}  // namespace simple

#endif