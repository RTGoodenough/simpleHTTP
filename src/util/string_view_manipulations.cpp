
#include <spdlog/spdlog.h>

#include <util/string_view_manipulations.hpp>

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