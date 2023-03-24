/**
 * @file socket.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_SOCKET_HPP
#define SIMPLE_HTTP_SOCKET_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

#include <server/server.types.hpp>
#include <socket/socket.types.hpp>

namespace simpleHTTP {
class SocketException : public std::runtime_error {
 public:
  SocketException(const std::string& message) : std::runtime_error(message) {}
  static void Throw(const std::string& message) { throw SocketException(message); }
};

class Socket {
 public:
  Socket(port);
  ~Socket();

  [[nodiscard]] size_t       poll_wait();
  [[nodiscard]] epoll_data_t getEvents(size_t i) const;
  [[nodiscard]] sock_fd      fd() const;

  void Shutdown();
  void newConnection();
  void closeConnection(sock_fd sock);

 private:
  sock_fd sock;
  sock_fd pollfd;

  sockaddr_in addr;
  socklen_t   addrlen = sizeof(addr);

  static const int maxEv = 1000;
  static const int maxConnections = 1000;

  epoll_event pollEv;
  epoll_event events[maxEv];
};
}  // namespace simpleHTTP

#endif