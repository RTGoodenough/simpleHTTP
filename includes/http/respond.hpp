#ifndef HTTP_BUILDER_HPP
#define HTTP_BUILDER_HPP

#include <http/http.types.hpp>
#include <pages/page_content.hpp>
#include <socket/socket.hpp>
#include <types/data.types.hpp>

namespace simpleHTTP {
namespace Respond {
[[nodiscard]] ByteVector WebPage(const PageContent&, Socket&);
[[nodiscard]] ByteVector NotFound(const HTTP::Request&, Socket&);
}  // namespace Respond
}  // namespace simpleHTTP

#endif