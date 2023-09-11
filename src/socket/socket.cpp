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

#include <fcntl.h>
#include <socket/socket.hpp>

simple::Socket::~Socket() { shutdownSock(); }

simple::Socket::Socket(port prt)
    : _sock(socket(AF_INET, SOCK_STREAM, 0)), _pollfd(), _addr(), _pollEv(), _events() {
  if (_sock < 0) {
    SocketException::error("Unable To Create Socket");
  }

  int opt = 1;
  if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
    SocketException::error("Unable To Set Socket Options");
    shutdownSock();
  }

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(prt);

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast) - Required for fitting C function
  if (bind(_sock, reinterpret_cast<struct sockaddr*>(&_addr), sizeof(_addr)) < 0) {
    SocketException::error("Unable To Bind Socket: ERRNO: " + std::to_string(errno));
    shutdownSock();
  }

  int create = (_pollfd = epoll_create1(0));
  if (create < 0) {
    SocketException::error("Unable To Create epoll: ERRNO: " + std::to_string(errno));
    shutdownSock();
  }

  _pollEv.events = EPOLLIN;
  _pollEv.data.fd = _sock;
  if (epoll_ctl(_pollfd, EPOLL_CTL_ADD, _sock, &_pollEv) < 0) {
    SocketException::error("Unable To Add Socket To epoll: ERRNO: " + std::to_string(errno));
    shutdownSock();
  }

  if (listen(_sock, MAX_CONNECTIONS) < 0) {
    SocketException::error("Unable To Start Listening On Socket: ERRNO: " + std::to_string(errno));
    shutdownSock();
  }
}

auto simple::Socket::pollWait() -> size_t {
  int evCnt = epoll_wait(_pollfd, _events.data(), MAX_EV, -1);
  if (evCnt < 0) {
    SocketException::error("Error waiting for event in epoll: ERRNO:" + std::to_string(errno));
    shutdownSock();
  }

  return static_cast<size_t>(evCnt);
}

auto simple::Socket::getEvents(size_t index) const -> epoll_data_t { return _events.at(index).data; }

void simple::Socket::newConnection() {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast) - Required for fitting C function
  sock_fd newSock = accept(_sock, reinterpret_cast<struct sockaddr*>(&_addr), &_addrlen);
  if (newSock == -1) {
    return;
  }

  // NOLINTNEXTLINE(hicpp-vararg, cppcoreguidelines-pro-type-vararg) - TODO: figure the best way to fit this
  fcntl(newSock, F_SETFL, SOCK_NONBLOCK);
  _pollEv.events = EPOLLIN;
  _pollEv.data.fd = newSock;
  if (epoll_ctl(_pollfd, EPOLL_CTL_ADD, newSock, &_pollEv) == -1) {
    close(newSock);
    return;
  }
}

void simple::Socket::closeConnection(sock_fd sck) {
  if (_pollfd != 0) {
    if (epoll_ctl(_pollfd, EPOLL_CTL_DEL, sck, &_pollEv) == -1) {
    }
  }
  close(sck);
}

// NOLINTNEXTLINE(readability-make-member-function-const) - Technically could be const, but it affects the socket
void simple::Socket::shutdownSock() {
  if (_sock != 0) {
    shutdown(_sock, SHUT_RDWR);
    close(_sock);
  }
  if (_pollfd != 0) {
    close(_pollfd);
  }
}

auto simple::Socket::fd() const -> simple::sock_fd { return _sock; }