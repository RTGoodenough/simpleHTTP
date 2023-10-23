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
#include <mutex>
#include <stdexcept>
#include <string>

#include <server/server.types.hpp>
#include <socket/socket.types.hpp>
#include "util/class_types.hpp"

namespace simple {
class SocketException : public std::runtime_error {
 public:
  explicit SocketException(const std::string& message) : std::runtime_error(message) {}
  static void error(const std::string& message) { throw SocketException(message); }
};

class Socket {
  NON_DEFAULT_CONSTRUCIBLE(Socket)
  DEFAULT_MOVEABLE(Socket)
  NON_COPYABLE(Socket)

 public:
  explicit Socket(port);

  [[nodiscard]] auto poll_wait() -> size_t;
  [[nodiscard]] auto get_events(size_t) const -> epoll_data_t;
  [[nodiscard]] auto fd() const -> sock_fd;

  void shutdown_sock();
  void new_connection();
  void close_connection(sock_fd);

  auto lock() -> std::unique_lock<std::mutex>;

 private:
  sock_fd _sock{};
  sock_fd _pollfd{};

  sockaddr_in _addr{};
  socklen_t   _addrlen = sizeof(_addr);

  static const int MAX_EV = 1000;
  static const int MAX_CONNECTIONS = 1000;

  epoll_event                     _pollEv{};
  std::array<epoll_event, MAX_EV> _events{};

 public:
  ~Socket();
};

}  // namespace simple

#endif