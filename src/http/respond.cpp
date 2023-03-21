

#include <http/respond.hpp>

namespace simpleHTTP {
namespace Respond {
void
WebPage(const PageContent& content, sock_fd socket) {
  ByteVector data;
}

void
NotFound(std::string_view, sock_fd) {}

void
BadRequest(sock_fd socket) {}

}  // namespace Respond
}  // namespace simpleHTTP
