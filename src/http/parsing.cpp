
#include <spdlog/spdlog.h>

#include <http/parsing.hpp>
#include <util/string_view_manipulations.hpp>

namespace simpleHTTP {
namespace Parsing {

std::optional<std::string_view>
getRoute(std::string_view req) {

  auto requestLine = split_first(req, "\r\n");
  if (requestLine.empty())
    return std::nullopt;

  size_t start = requestLine.find(" /");
  if (start == std::string_view::npos)
    return std::nullopt;

  size_t end = requestLine.find_last_of(' ');
  if (end == std::string_view::npos || end <= start)
    return std::nullopt;

  return requestLine.substr(start + 1, end - start);
}

}  // namespace Parsing
}  // namespace simpleHTTP