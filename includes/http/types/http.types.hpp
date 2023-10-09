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
#include <string_view>

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

enum class Version {
  HTTP1,
  HTTP11,
  INVALID,
};

enum class Scheme {
  HTTP,
  HTTPS,
};

enum class UriForm {
  ORIGIN,
  ABSOLUTE,
  AUTHORITY,
  ASTERISK,
  INVALID,
};

struct UriTarget {
  Scheme           scheme;
  std::string_view host;
  std::string_view uri;
  std::string_view port;
};

inline auto method_from_str(std::string_view method) -> Method {
  static const std::map<std::string, Method, std::less<>> M_MAP = {
      {"GET", Method::GET},       {"PUT", Method::PUT},         {"POST", Method::POST},
      {"DELETE", Method::DELETE}, {"CONNECT", Method::CONNECT}, {"OPTIONS", Method::OPTIONS},
      {"HEAD", Method::HEAD},     {"TRACE", Method::TRACE},     {"PATCH", Method::PATCH},
  };
  auto iter = M_MAP.find(method);
  if (iter == M_MAP.end()) return Method::INVALID;

  return iter->second;
}

inline auto version_from_str(std::string_view version) -> Version {
  static const std::map<std::string, Version, std::less<>> V_MAP = {
      {"HTTP/1.0", Version::HTTP1},
      {"HTTP/1.1", Version::HTTP11},
  };

  auto iter = V_MAP.find(version);
  if (iter == V_MAP.end()) return Version::INVALID;

  return iter->second;
}

}  // namespace simple::http

#endif