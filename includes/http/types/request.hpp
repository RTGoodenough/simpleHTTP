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
  [[nodiscard]] inline auto get_header(Header hdrType) const -> std::string_view {
    auto iter = _headers.find(hdrType);
    if (iter == _headers.end()) return {};

    return iter->second;
  }
  [[nodiscard]] inline auto get_uri() const -> http::UriTarget { return _uri; }
  [[nodiscard]] inline auto get_method() const -> http::Method { return _method; }
  [[nodiscard]] inline auto get_content() const -> std::string_view { return _content; }
  [[nodiscard]] inline auto get_verion() const -> http::Version { return _version; }
  [[nodiscard]] inline auto get_query() const -> std::string_view { return _query; }
  [[nodiscard]] inline auto get_form() const -> http::UriForm { return _uriForm; }

  inline void set_uri(http::UriTarget uri) { _uri = uri; }
  inline void set_target_host(std::string_view host) { _uri.host = host; }
  inline void set_target_scheme(http::Scheme scheme) { _uri.scheme = scheme; }
  inline void set_target_port(std::string_view port) { _uri.port = port; }
  inline void set_header(Header hdr, std::string_view val) { _headers[hdr] = val; }
  inline void set_content(std::string_view content) { _content = content; }
  inline void set_method(http::Method method) { _method = method; }
  inline void set_version(std::string_view version) { _version = version_from_str(version); }
  inline void set_query(std::string_view query) { _query = query; }
  inline void set_uri_form(UriForm form) { _uriForm = form; }

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