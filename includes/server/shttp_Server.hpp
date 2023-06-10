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

#include <http/parsing.hpp>
#include <pages/page_manager.hpp>
#include <server/server.types.hpp>
#include <socket/socket.hpp>
#include <types/data.types.hpp>

namespace simple {

constexpr port DEFAULT_PORT = 9000;

class ServerException : public std::runtime_error {
 public:
  explicit ServerException(const std::string& message) : std::runtime_error(message) {}
  static void error(const std::string& message) { throw ServerException(message); }
};

class Server {
 public:
  Server(Socket srvSock, Pages pages)
      : _srvSock(std::move(srvSock)), _pages(std::move(pages)) {}

  Server& start();

 private:
  Socket _srvSock;
  Pages  _pages;

  void handleEvents(size_t);
  void handleData(sock_fd);
  void handleRequest(sock_fd, const char*, size_t);

 public:
  Server() : _srvSock(DEFAULT_PORT) {}
  Server(const Server&) = default;
  Server(Server&&) = default;
  Server& operator=(const Server&) = default;
  Server& operator=(Server&&) = default;
  ~Server() = default;
};
}  // namespace simple

#endif