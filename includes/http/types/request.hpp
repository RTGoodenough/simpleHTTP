/**
 * @file request.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_REQUEST_HPP
#define SIMPLE_HTTP_REQUEST_HPP

#include <string_view>
#include <unordered_map>

#include <iostream>

#include <httpparser/request.h>

#include <http/types/header.types.hpp>
#include <http/types/http.types.hpp>

namespace simple::http {
class Request {
 public:
  [[nodiscard]] inline std::string_view getHeader(Header hdrType) const {
    return _headers.at(hdrType);
  }
  [[nodiscard]] inline std::string_view     getUri() const { return _uri; }
  [[nodiscard]] inline http::Method         getMethod() const { return _method; }
  [[nodiscard]] inline std::string_view     getContent() const { return _content; }
  [[nodiscard]] inline httpparser::Request& request() { return _req; };

  inline void update() { load(); }

 private:
  http::Method                                 _method{Method::GET};
  std::string_view                             _uri;
  std::unordered_map<Header, std::string_view> _headers;
  std::string_view                             _content;

  // TODO(rolland): remove with custom parser
  httpparser::Request _req;
  inline void         load() {
    _method = methodFromStr(_req.method);
    _uri = _req.uri;

    for (const auto& hdr : _req.headers) {
      _headers[headerFromStr(hdr.name)] = hdr.value;
    }

    _content = std::string_view(_req.content.data(), _req.content.size());
  }

 public:
  Request() = default;
  ~Request() = default;
  Request(const Request& other) : _method(other._method), _req(other._req) { load(); };
  Request(Request&& other) noexcept
      : _method(other._method), _req(std::move(other._req)) {
    load();
  };
  Request& operator=(const Request& other) {
    if (&other == this) {
      return *this;
    }

    _method = other._method;
    _req = other._req;
    load();
    return *this;
  };
  Request& operator=(Request&& other) noexcept {
    _method = other._method;
    _req = std::move(other._req);
    load();
    return *this;
  };
};
}  // namespace simple::http

#endif