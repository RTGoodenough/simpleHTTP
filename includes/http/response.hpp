/**
 * @file response.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_RESPONSE_HPP
#define SIMPLE_HTTP_RESPONSE_HPP

#include <pages/page_content.hpp>

#include <http/types/header.types.hpp>
#include <http/types/status.types.hpp>
#include <types/data.types.hpp>

namespace simple::http {
class Response {
 public:
  ByteVector build();

  Response&            setStatus(Status);
  [[nodiscard]] Status getStatus() const;

  Response&                      setHeader(Header, std::string_view);
  [[nodiscard]] std::string_view getHeader(Header) const;

  Response& setContent(PageContentView);

  Response& setContentType(Content);

 private:
  Status                                       _status;
  std::unordered_map<Header, std::string_view> _headers;
  PageContentView                              _page;
  std::string                                  _content_length;

  size_t totalLength() const;

  inline void        buildAddResponseLine(ByteVector&) const;
  static inline void buildAddHeader(Header, std::string_view, ByteVector&);
  static inline void buildAddContent(PageContentView, ByteVector&);
};
}  // namespace simple::http

#endif