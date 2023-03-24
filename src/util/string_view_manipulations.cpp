
#include <util/string_view_manipulations.hpp>

std::string_view
simpleHTTP::split_first(std::string_view str, std::string_view delim) {
  const size_t sz = str.find(delim);
  if (sz == std::string_view::npos)
    return {};

  return {str.begin(), sz};
}