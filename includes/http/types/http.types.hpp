/**
 * @file http.types.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_HTTP_TYPES_HPP
#define SIMPLE_HTTP_HTTP_TYPES_HPP

#include <map>
#include <string>

namespace simple::http {
enum class Method {
  GET,
  PUT,
  POST,
  DELETE,
  CONNECT,
  OPTIONS,
  HEAD,
  TRACE,
  PATCH,
  INVALID,
};

struct Uri {
  std::string_view scheme;
  std::string_view host;
  std::string_view port;
};

inline Method methodFromStr(std::string_view method) {
  static const std::map<std::string, Method, std::less<>> M_MAP = {
      {"GET", Method::GET},         {"PUT", Method::PUT},
      {"POST", Method::POST},       {"DELETE", Method::DELETE},
      {"CONNECT", Method::CONNECT}, {"OPTIONS", Method::OPTIONS},
      {"HEAD", Method::HEAD},       {"TRACE", Method::TRACE},
      {"PATCH", Method::PATCH},
  };
  auto iter = M_MAP.find(method);
  if (iter == M_MAP.end()) return Method::INVALID;

  return iter->second;
}
}  // namespace simple::http

#endif