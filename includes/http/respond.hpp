#ifndef HTTP_BUILDER_HPP
#define HTTP_BUILDER_HPP

#include <string_view>

#include <http/http.types.hpp>
#include <pages/page_content.hpp>
#include <socket/socket.types.hpp>
#include <types/data.types.hpp>

namespace simpleHTTP {
namespace Respond {
void WebPage(const PageContent&, sock_fd);
void NotFound(std::string_view, sock_fd);
void BadRequest(sock_fd);
}  // namespace Respond
}  // namespace simpleHTTP

#endif