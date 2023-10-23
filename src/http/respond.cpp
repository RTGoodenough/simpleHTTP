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
inline void send_data(const ByteVector& data, sock_fd socket) {
  if (send(socket, data.data(), data.size(), MSG_NOSIGNAL) == -1) {
    warn("Failed to Send Data To:" + std::to_string(socket));
  }
}
}  // namespace

void web_page(http::Status status, PageContentView content, sock_fd socket) {
  http::Response res;
  res.set_status(status).set_content(content);
  send_data(res.build(), socket);
}

void bad_request(sock_fd socket) {
  http::Response res;

  res.set_status(http::Status::BAD_REQUEST);

  auto data = res.build();
  send_data(data, socket);
}

}  // namespace simple::respond