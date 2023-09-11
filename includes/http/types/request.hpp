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

#include <iostream>
#include <string_view>
#include <unordered_map>

#include "http/types/header.types.hpp"
#include "http/types/http.types.hpp"

namespace simple::http {
class Request {
 public:
  [[nodiscard]] inline auto getHeader(Header hdrType) const -> std::string_view {
    auto iter = _headers.find(hdrType);
    if (iter == _headers.end()) return {};

    return iter->second;
  }
  [[nodiscard]] inline auto getUri() const -> http::UriTarget { return _uri; }
  [[nodiscard]] inline auto getMethod() const -> http::Method { return _method; }
  [[nodiscard]] inline auto getContent() const -> std::string_view { return _content; }
  [[nodiscard]] inline auto getVerion() const -> http::Version { return _version; }
  [[nodiscard]] inline auto getQuery() const -> std::string_view { return _query; }
  [[nodiscard]] inline auto getForm() const -> http::UriForm { return _uriForm; }

  inline void setUri(http::UriTarget uri) { _uri = uri; }
  inline void setTargetHost(std::string_view host) { _uri.host = host; }
  inline void setTargetScheme(http::Scheme scheme) { _uri.scheme = scheme; }
  inline void setTargetPort(std::string_view port) { _uri.port = port; }
  inline void setHeader(Header hdr, std::string_view val) { _headers[hdr] = val; }
  inline void setContent(std::string_view content) { _content = content; }
  inline void setMethod(http::Method method) { _method = method; }
  inline void setVersion(std::string_view version) { _version = versionFromStr(version); }
  inline void setQuery(std::string_view query) { _query = query; }
  inline void setUriForm(UriForm form) { _uriForm = form; }

 private:
  http::Method                                 _method{Method::GET};
  http::UriTarget                              _uri;
  http::UriForm                                _uriForm{UriForm::INVALID};
  http::Version                                _version{Version::INVALID};
  std::unordered_map<Header, std::string_view> _headers{};
  std::string_view                             _content;
  std::string_view                             _query;

 public:
  Request() = default;
  ~Request() = default;
  Request(const Request& other) = default;
  Request(Request&& other) noexcept = default;
  auto operator=(const Request& other) -> Request& = default;
  auto operator=(Request&& other) noexcept -> Request& = default;
};
}  // namespace simple::http

#endif