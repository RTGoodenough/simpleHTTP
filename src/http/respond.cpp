
#include <string.h>
#include <sys/socket.h>

#include <iostream>

#include <http/respond.hpp>
#include <http/response.hpp>
#include <http/types/status.types.hpp>

namespace simpleHTTP {

namespace Respond {
void
WebPage(PageContent content, sock_fd socket) {
  Response res;
  res.setStatus(Status::OK).setContent(content);
  auto data = res.build();

  send(socket, data.data(), data.size(), 0);
}

void
NotFound(std::string_view, sock_fd) {}

void
BadRequest(sock_fd socket) {}

}  // namespace Respond
}  // namespace simpleHTTP
