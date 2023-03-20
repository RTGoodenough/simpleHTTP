#ifndef YASUMI_SOCKET_HPP
#define YASUMI_SOCKET_HPP

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