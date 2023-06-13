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

#include <http/types/header.types.hpp>
#include <http/types/http.types.hpp>

namespace simple::http {
class Request {
 public:
  [[nodiscard]] inline std::string_view getHeader(Header hdrType) const {
    return _headers.at(hdrType);
  }
  [[nodiscard]] inline http::Uri        getUri() const { return _uri; }
  [[nodiscard]] inline http::Method     getMethod() const { return _method; }
  [[nodiscard]] inline std::string_view getContent() const { return _content; }

  inline void setUri(http::Uri uri) { _uri = uri; }
  inline void setHeader(Header hdr, std::string_view val) { _headers.at(hdr) = val; }
  inline void setContent(std::string_view content) { _content = content; }
  inline void setMethod(http::Method method) { _method = method; }

 private:
  http::Method                                 _method{Method::GET};
  http::Uri                                    _uri;
  std::unordered_map<Header, std::string_view> _headers;
  std::string_view                             _content;

 public:
  Request() = default;
  ~Request() = default;
  Request(const Request& other) = default;
  Request(Request&& other) noexcept = default;
  Request& operator=(const Request& other) = default;
  Request& operator=(Request&& other) noexcept = default;
};
}  // namespace simple::http

#endif