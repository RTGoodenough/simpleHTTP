/**
 * @file response.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <cstddef>
#include <string>

#include "http/response.hpp"
#include "http/types/header.types.hpp"
#include "http/types/status.types.hpp"
#include "pages/page_content.hpp"

namespace simple {

namespace {
inline auto get_version() -> const std::string& {
  static const std::string HTTP_VERSION = "HTTP/1.1";
  return HTTP_VERSION;
}

inline auto get_line_end() -> const std::string& {
  static const std::string LINE_END = "\r\n";
  return LINE_END;
}
}  // namespace

auto http::Response::build() -> ByteVector {
  size_t length = total_length();

  ByteVector data;
  data.reserve(length);

  build_add_response_line(data);
  for (const auto [header, value] : _headers) {
    build_add_header(header, value, data);
  }
  build_add_content(_page, data);

  return data;
}

auto http::Response::set_status(Status stat) -> http::Response& {
  _status = stat;
  return *this;
}

auto http::Response::get_status() const -> http::Status { return _status; }

auto http::Response::set_header(Header header, std::string_view val) -> http::Response& {
  _headers[header] = val;
  return *this;
}

auto http::Response::get_header(Header header) const -> std::string_view {
  if (_headers.find(header) == _headers.end()) {
    return {};
  }

  return _headers.at(header);
}

auto http::Response::set_content(PageContentView content) -> http::Response& {
  _page = content;
  _content_length = std::to_string(content.size);
  set_header(Header::CONTENT_TYPE, to_content_str(content.type))
      .set_header(Header::CONTENT_LENGTH, _content_length);
  return *this;
}

auto http::Response::total_length() const -> size_t {
  size_t length = 0;

  length += get_version().length() + to_status_str(_status).length() + get_line_end().length();

  for (auto [header, value] : _headers) {
    length += to_header_str(header).length() + value.length() + get_line_end().length();
  }

  length += get_line_end().length();

  length += _page.size;

  return length;
}

inline void http::Response::build_add_response_line(ByteVector& data) const {
  const auto& statusStr = to_status_str(_status);
  const auto& statusNumberStr = to_status_num_str(_status);

  auto iter = data.insert(data.end(), get_version().begin(), get_version().end()) +
              static_cast<std::ptrdiff_t>(get_version().length());
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, statusNumberStr.begin(), statusNumberStr.end()) +
         static_cast<std::ptrdiff_t>(statusNumberStr.length());
  iter = data.insert(iter, ' ') + 1;
  iter =
      data.insert(iter, statusStr.begin(), statusStr.end()) + static_cast<std::ptrdiff_t>(statusStr.length());
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, get_line_end().begin(), get_line_end().end()) +
         static_cast<std::ptrdiff_t>(get_line_end().length());
}

inline void http::Response::build_add_header(Header type, const std::string_view value, ByteVector& data) {
  const auto& headerStr = to_header_str(type);

  auto iter = data.insert(data.end(), headerStr.begin(), headerStr.end()) +
              static_cast<std::ptrdiff_t>(headerStr.length());
  iter = data.insert(iter, ':') + 1;
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, value.begin(), value.end()) + static_cast<std::ptrdiff_t>(value.length());
  iter = data.insert(iter, get_line_end().begin(), get_line_end().end()) +
         static_cast<std::ptrdiff_t>(get_line_end().length());
}

inline void http::Response::build_add_content(PageContentView content, ByteVector& data) {
  auto iter = data.insert(data.end(), get_line_end().begin(), get_line_end().end()) +
              static_cast<std::ptrdiff_t>(get_line_end().length());
  iter = data.insert(iter, content.data, std::next(content.data, static_cast<std::ptrdiff_t>(content.size))) +
         static_cast<std::ptrdiff_t>(content.size);
}

}  // namespace simple