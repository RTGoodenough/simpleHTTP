
#include <string.h>

#include <http/response.hpp>

namespace simpleHTTP {

const std::string HTTP_version = "HTTP/1.1";
const std::string lineEnd = "\r\n";

ByteVector
Response::build() {
  size_t     length = totalLength();
  ByteVector data;
  data.reserve(length);

  build_addResponseLine(data);
  for (const auto [header, value] : headers) {
    build_addHeader(header, value, data);
  }
  if (page.file.content != nullptr)
    build_addContent(page, data);

  return data;
}

Response&
Response::setStatus(Status stat) {
  status = stat;
  return *this;
}

Status
Response::getStatus() const {
  return status;
}

Response&
Response::setHeader(HeaderType header, std::string_view val) {
  headers[header] = val;
  return *this;
}

const std::string_view
Response::getHeader(HeaderType header) const {
  if (headers.find(header) == headers.end())
    return {};

  return headers.at(header);
}

Response&
Response::setContent(PageContent content) {
  page = content;
  content_length = std::to_string(content.file.length);
  setHeader(CONTENT_TYPE, ContentTypeStrs.at(content.type)).setHeader(CONTENT_LENGTH, content_length);
  return *this;
}

size_t
Response::totalLength() const {
  size_t length = 0;

  length += HTTP_version.length() + StatusStrs.at(status).length() + lineEnd.length();

  for (auto [header, value] : headers) {
    length += HeaderStrs.at(header).length() + value.length() + lineEnd.length();
  }

  length += lineEnd.length();

  if (page.file.content != nullptr)
    length += page.file.length;

  return length;
}

inline void
Response::build_addResponseLine(ByteVector& data) const {
  const auto& statusStr = StatusStrs.at(status);
  const auto& statusNumberStr = StatusNumberStrs.at(status);

  auto iter = data.insert(data.end(), HTTP_version.begin(), HTTP_version.end()) + HTTP_version.length();
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, statusNumberStr.begin(), statusNumberStr.end()) + statusNumberStr.length();
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, statusStr.begin(), statusStr.end()) + statusStr.length();
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, lineEnd.begin(), lineEnd.end()) + lineEnd.length();
}

inline void
Response::build_addHeader(HeaderType type, const std::string_view value, ByteVector& data) const {
  const auto& headerStr = HeaderStrs.at(type);

  auto iter = data.insert(data.end(), headerStr.begin(), headerStr.end()) + headerStr.length();
  iter = data.insert(iter, ':') + 1;
  iter = data.insert(iter, ' ') + 1;
  iter = data.insert(iter, value.begin(), value.end()) + value.length();
  iter = data.insert(iter, lineEnd.begin(), lineEnd.end()) + lineEnd.length();
}

inline void
Response::build_addContent(PageContent content, ByteVector& data) const {
  auto iter = data.insert(data.end(), lineEnd.begin(), lineEnd.end()) + lineEnd.length();
  iter = data.insert(iter, content.file.content, content.file.content + content.file.length) + content.file.length;
}

}  // namespace simpleHTTP