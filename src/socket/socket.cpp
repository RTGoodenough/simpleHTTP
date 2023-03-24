/**
 * @file socket.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <socket/socket.hpp>

simpleHTTP::Socket::~Socket() {
  Shutdown();
}

simpleHTTP::Socket::Socket(port p) {
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    SocketException::Throw("Unable To Create Socket");
  }

  int opt = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
    SocketException::Throw("Unable To Set Socket Options");
    Shutdown();
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(p);

  if (bind(sock, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
    SocketException::Throw("Unable To Bind Socket: ERRNO: " + std::to_string(errno));
    Shutdown();
  }

  if ((pollfd = epoll_create1(0)) < 0) {
    SocketException::Throw("Unable To Create epoll: ERRNO: " + std::to_string(errno));
    Shutdown();
  }

  pollEv.events = EPOLLIN;
  pollEv.data.fd = sock;
  if (epoll_ctl(pollfd, EPOLL_CTL_ADD, sock, &pollEv) < 0) {
    SocketException::Throw("Unable To Add Socket To epoll: ERRNO: " + std::to_string(errno));
    Shutdown();
  }

  if (listen(sock, maxConnections) < 0) {
    SocketException::Throw("Unable To Start Listening On Socket: ERRNO: " + std::to_string(errno));
    Shutdown();
  }
}

size_t
simpleHTTP::Socket::poll_wait() {
  int evCnt = epoll_wait(pollfd, events, maxEv, -1);
  if (evCnt < 0) {
    SocketException::Throw("Error waiting for event in epoll: ERRNO:" + std::to_string(errno));
    Shutdown();
  }

  return static_cast<size_t>(evCnt);
}

epoll_data_t
simpleHTTP::Socket::getEvents(size_t i) const {
  return events[i].data;
}

void
simpleHTTP::Socket::newConnection() {
  sock_fd newSock = accept(sock, reinterpret_cast<struct sockaddr*>(&addr), &addrlen);
  if (newSock == -1) {
    return;
  }

  fcntl(newSock, F_SETFL, SOCK_NONBLOCK);
  pollEv.events = EPOLLIN;
  pollEv.data.fd = newSock;
  if (epoll_ctl(pollfd, EPOLL_CTL_ADD, newSock, &pollEv) == -1) {
    close(newSock);
    return;
  }
}

void
simpleHTTP::Socket::closeConnection(sock_fd sck) {
  if (pollfd != 0) {
    if (epoll_ctl(pollfd, EPOLL_CTL_DEL, sck, &pollEv) == -1) {}
  }
  close(sck);
}

void
simpleHTTP::Socket::Shutdown() {
  if (sock != 0) {
    shutdown(sock, SHUT_RDWR);
    close(sock);
  }
  if (pollfd != 0) {
    close(pollfd);
  }
}

simpleHTTP::sock_fd
simpleHTTP::Socket::fd() const {
  return sock;
}