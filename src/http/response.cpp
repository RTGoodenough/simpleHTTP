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

#include <cstring>

#include <http/response.hpp>
#include <string>
#include "http/types/header.types.hpp"
#include "http/types/status.types.hpp"
#include "pages/page_content.hpp"

namespace simple {

namespace {
inline const std::string& getVersion() {
  static const std::string HTTP_VERSION = "HTTP/1.1";
  return HTTP_VERSION;
}

inline const std::string& getLineEnd() {
  static const std::string LINE_END = "\r\n";
  return LINE_END;
}
}  // namespace

ByteVector http::Response::build() {
  size_t length = totalLength();

  ByteVector data;
  data.reserve(length);

  buildAddResponseLine(data);
  for (const auto [header, value] : _headers) {
    buildAddHeader(header, value, data);
  }
  buildAddContent(_page, data);

  return data;
}

http::Response& http::Response::setStatus(Status stat) {
  _status = stat;
  return *this;
}

http::Status http::Response::getStatus() const { return _status; }

http::Response& http::Response::setHeader(Header header, std::string_view val) {
  _headers[header] = val;
  return *this;
}

std::string_view http::Response::getHeader(Header header) const {
  if (_headers.find(header) == _headers.end()) {
    return {};
  }

  return _headers.at(header);
}

http::Response& http::Response::setContent(PageContentView content) {
  _page = content;
  _content_length = std::to_string(content.size);
  setHeader(Header::CONTENT_TYPE, toContentStr(content.type))
      .setHeader(Header::CONTENT_LENGTH, _content_length);
  return *this;
}

size_t http::Response::totalLength() const {
  size_t length = 0;

  length += getVersion().length() + toStatusStr(_status).length() + getLineEnd().length();

  for (auto [header, value] : _headers) {
    length += toHeaderStr(header).length() + value.length() + getLineEnd().length();
  }

  length += getLineEnd().length();

  length += _page.size;

  return length;
}

inline void http::Response::buildAddResponseLine(ByteVector& data) const {
  const auto& statusStr = toStatusStr(_status);
  const auto& statusNumberStr = toStatusNumStr(_status);

  auto iter = data.insert(data.end(), getVersion().begin(), getVersion().end()) +
              static_cast<std::ptrdiff_t>(getVersion().length());
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, statusNumberStr.begin(), statusNumberStr.end()) +
         static_cast<std::ptrdiff_t>(statusNumberStr.length());
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, statusStr.begin(), statusStr.end()) +
         static_cast<std::ptrdiff_t>(statusStr.length());
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, getLineEnd().begin(), getLineEnd().end()) +
         static_cast<std::ptrdiff_t>(getLineEnd().length());
}

inline void http::Response::buildAddHeader(Header type, const std::string_view value,
                                           ByteVector& data) {
  const auto& headerStr = toHeaderStr(type);

  auto iter = data.insert(data.end(), headerStr.begin(), headerStr.end()) +
              static_cast<std::ptrdiff_t>(headerStr.length());
  iter = data.insert(iter, ':') + 1;
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, value.begin(), value.end()) +
         static_cast<std::ptrdiff_t>(value.length());
  iter = data.insert(iter, getLineEnd().begin(), getLineEnd().end()) +
         static_cast<std::ptrdiff_t>(getLineEnd().length());
}

inline void http::Response::buildAddContent(PageContentView content, ByteVector& data) {
  auto iter = data.insert(data.end(), getLineEnd().begin(), getLineEnd().end()) +
              static_cast<std::ptrdiff_t>(getLineEnd().length());
  iter = data.insert(iter, content.data, content.data + content.size) +
         static_cast<std::ptrdiff_t>(content.size);
}

}  // namespace simple