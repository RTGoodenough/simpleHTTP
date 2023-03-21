
#include <spdlog/spdlog.h>

#include <util/string_view_manipulations.hpp>

std::string_view
simpleHTTP::split_first(std::string_view str, std::string_view delim) {
  const size_t sz = str.find(delim);
  if (sz == std::string_view::npos)
    return {};

  return {str.begin(), sz};
}

simpleHTTP::SubStrs
simpleHTTP::split(std::string_view str, std::string_view delim) {
  simpleHTTP::SubStrs substrs{};
  size_t              prevPos = 0;
  size_t              currPos = str.find(delim);

  while (currPos != std::string_view::npos && prevPos < str.size()) {
    substrs.emplace_back(str.substr(prevPos, (currPos - prevPos)));
    prevPos = currPos + delim.size();
    currPos = str.find(delim, prevPos);
  }

  substrs.emplace_back(str.substr(prevPos, (currPos - prevPos)));
  return substrs;
}