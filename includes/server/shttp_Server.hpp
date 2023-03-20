#ifndef YASUMI_SERVER_HPP
#define YASUMI_SERVER_HPP

#include <iostream>
#include <signal.h>
#include <stdexcept>
#include <string>

#include <routing/router.hpp>
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
  Server() : srvSock(9000), router() {}
  ~Server() = default;

  Server& start();

  void setRouter(Router&);

 private:
  Socket srvSock;
  Router router;

  void handleEvents(size_t);
  void handleData(sock_fd);
  void handleRequest(sock_fd, const char*);
  void respond(sock_fd, const ByteVector&);
};
}  // namespace simpleHTTP

#endif