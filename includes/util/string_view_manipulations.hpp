#ifndef YASUMI_STRING_VIEW_MANIPULATIONS_HPP
#define YASUMI_STRING_VIEW_MANIPULATIONS_HPP

#include <string>
#include <string_view>
#include <vector>

namespace simpleHTTP {
typedef std::vector<std::string_view> SubStrs;

SubStrs split(std::string_view str, std::string_view delim);
SubStrs getLines(std::string_view str);
}  // namespace simpleHTTP

#endif