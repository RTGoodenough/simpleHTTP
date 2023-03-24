/**
 * @file parsing.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <spdlog/spdlog.h>

#include <http/parsing.hpp>
#include <util/string_view_manipulations.hpp>

namespace simpleHTTP {
namespace Parsing {

std::optional<std::string_view>
getRoute(std::string_view req) {

  auto requestLine = split_first(req, "\r\n");
  if (requestLine.empty()) {
    return std::nullopt;
  }

  size_t start = requestLine.find(" /");
  if (start == std::string_view::npos) {
    return std::nullopt;
  }

  size_t end = requestLine.find_last_of(' ');
  if (end == std::string_view::npos || end <= start) {
    return std::nullopt;
  }

  return requestLine.substr(start + 1, end - start - 1);
}

}  // namespace Parsing
}  // namespace simpleHTTP