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

#include <iostream>
#include <signal.h>
#include <stdexcept>
#include <string>

#include <http/parsing.hpp>
#include <pages/page_manager.hpp>
#include <server/server.types.hpp>
#include <socket/socket.hpp>
#include <types/data.types.hpp>

namespace simpleHTTP {
class ServerException : public std::runtime_error {
 public:
  ServerException(const std::string& message) : std::runtime_error(message) {}
  static void Throw(const std::string& message) { throw ServerException(message); }
};

class Server {
 public:
  Server() : srvSock(9000) {}
  ~Server() = default;

  Server& start();

 private:
  Socket srvSock;
  Pages  pages;

  void handleEvents(size_t);
  void handleData(sock_fd);
  void handleRequest(sock_fd, const char*);
};
}  // namespace simpleHTTP

#endif