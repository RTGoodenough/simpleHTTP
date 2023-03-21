#ifndef YASUMI_SERVER_HPP
#define YASUMI_SERVER_HPP

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