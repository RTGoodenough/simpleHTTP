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

#include <string>
#include <unordered_map>

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
};

inline Method methodFromStr(const std::string& method) {
  static const std::unordered_map<std::string, Method> M_MAP = {
      {"GET", Method::GET},         {"PUT", Method::PUT},
      {"POST", Method::POST},       {"DELETE", Method::DELETE},
      {"CONNECT", Method::CONNECT}, {"OPTIONS", Method::OPTIONS},
      {"HEAD", Method::HEAD},       {"TRACE", Method::TRACE},
      {"PATCH", Method::PATCH},
  };
  return M_MAP.at(method);
}
}  // namespace simple::http

#endif