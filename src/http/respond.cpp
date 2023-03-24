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

#include <string.h>
#include <sys/socket.h>

#include <iostream>

#include <http/respond.hpp>
#include <http/response.hpp>
#include <http/types/status.types.hpp>

namespace simpleHTTP {

namespace Respond {

namespace {
inline void
Send(const ByteVector& data, sock_fd socket) {
  send(socket, data.data(), data.size(), 0);
}
}  // namespace

void
WebPage(Status status, PageContent content, sock_fd socket) {
  Response res;
  res.setStatus(status).setContent(content);
  Send(res.build(), socket);
}

void
BadRequest(sock_fd socket) {
  Response res;

  res.setStatus(Status::BAD_REQUEST);

  auto data = res.build();
  Send(data, socket);
}

}  // namespace Respond
}  // namespace simpleHTTP
