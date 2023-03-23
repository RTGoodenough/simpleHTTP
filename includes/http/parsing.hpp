#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <optional>
#include <string_view>

#include <http/types/status.types.hpp>
namespace simpleHTTP {
namespace Parsing {
[[nodiscard]] std::optional<std::string_view> getRoute(std::string_view);
}
}  // namespace simpleHTTP

#endif