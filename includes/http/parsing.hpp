#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <optional>
#include <string_view>

#include <http/http.types.hpp>
#include <routing/router.types.hpp>

namespace simpleHTTP {
namespace Parsing {
[[nodiscard]] std::optional<Route> getRoute(std::string_view);
}
}  // namespace simpleHTTP

#endif