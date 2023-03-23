#ifndef SIMPLE_HTTP_RESPONSE_HPP
#define SIMPLE_HTTP_RESPONSE_HPP

#include <pages/page_content.hpp>

#include <http/types/header.types.hpp>
#include <http/types/status.types.hpp>
#include <types/data.types.hpp>

namespace simpleHTTP {
class Response {
 public:
  ByteVector build();

  Response&            setStatus(Status);
  [[nodiscard]] Status getStatus() const;

  Response&                            setHeader(HeaderType, std::string_view);
  [[nodiscard]] const std::string_view getHeader(HeaderType) const;

  Response& setContent(PageContent);

  Response& ContentType(ContentType);

 private:
  Status                                           status;
  std::unordered_map<HeaderType, std::string_view> headers;
  PageContent                                      page;
  std::string                                      content_length;

  size_t totalLength() const;

  inline void build_addResponseLine(ByteVector&) const;
  inline void build_addHeader(HeaderType, const std::string_view, ByteVector&) const;
  inline void build_addContent(PageContent, ByteVector&) const;
};
}  // namespace simpleHTTP

#endif