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

#include <httpparser/httprequestparser.h>
#include <http/parsing.hpp>
#include <optional>
#include <util/string_view_manipulations.hpp>

namespace simple::http {

std::optional<Request> parse(std::string_view reqStr) {
  httpparser::HttpRequestParser parser;
  Request                       req;
  auto result = parser.parse(req.request(), reqStr.begin(), reqStr.end());
  if (result == parser.ParsingCompleted) {
    req.update();
    return req;
  }

  return std::nullopt;
}

}  // namespace simple::http