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

#include <array>
#include <stdexcept>
#include <string>

#include <server/server.types.hpp>
#include <socket/socket.types.hpp>

namespace simple {
class SocketException : public std::runtime_error {
 public:
  explicit SocketException(const std::string& message) : std::runtime_error(message) {}
  static void error(const std::string& message) { throw SocketException(message); }
};

class Socket {
 public:
  explicit Socket(port);

  [[nodiscard]] auto pollWait() -> size_t;
  [[nodiscard]] auto getEvents(size_t) const -> epoll_data_t;
  [[nodiscard]] auto fd() const -> sock_fd;

  void shutdownSock();
  void newConnection();
  void closeConnection(sock_fd);

 private:
  sock_fd _sock;
  sock_fd _pollfd;

  sockaddr_in _addr;
  socklen_t   _addrlen = sizeof(_addr);

  static const int MAX_EV = 1000;
  static const int MAX_CONNECTIONS = 1000;

  epoll_event                     _pollEv;
  std::array<epoll_event, MAX_EV> _events;

 public:
  Socket(const Socket&) = default;
  auto operator=(const Socket&) -> Socket& = default;
  Socket(Socket&&) = default;
  auto operator=(Socket&&) -> Socket& = default;
  ~Socket();
};

}  // namespace simple

#endif