/**
 * @file respond.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <sys/socket.h>
#include <cstring>

#include <iostream>

#include <http/respond.hpp>
#include <http/response.hpp>
#include <http/types/status.types.hpp>
#include <utility>

namespace simple::respond {

namespace {
inline void sendData(const ByteVector& data, sock_fd socket) {
  send(socket, data.data(), data.size(), 0);
}
}  // namespace

void webPage(http::Status status, PageContentView content, sock_fd socket) {
  http::Response res;
  res.setStatus(status).setContent(content);
  sendData(res.build(), socket);
}

void badRequest(sock_fd socket) {
  http::Response res;

  res.setStatus(http::Status::BAD_REQUEST);

  auto data = res.build();
  debug({data.data(), data.size()});
  sendData(data, socket);
}

}  // namespace simple::respond
