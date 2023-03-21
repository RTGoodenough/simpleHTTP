#ifndef YASUMI_STRING_VIEW_MANIPULATIONS_HPP
#define YASUMI_STRING_VIEW_MANIPULATIONS_HPP

#include <string>
#include <string_view>
#include <vector>

namespace simpleHTTP {

typedef std::vector<std::string_view> SubStrs;

std::string_view split_first(std::string_view str, std::string_view delim);
SubStrs          split(std::string_view str, std::string_view delim);

}  // namespace simpleHTTP

#endif