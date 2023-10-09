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

#include "pages/page_content.hpp"

#include "http/types/header.types.hpp"
#include "http/types/status.types.hpp"

#include "types/data.types.hpp"

namespace simple::http {
class Response {
 public:
  auto build() -> ByteVector;

  auto               set_status(Status) -> Response&;
  [[nodiscard]] auto get_status() const -> Status;

  auto               set_header(Header, std::string_view) -> Response&;
  [[nodiscard]] auto get_header(Header) const -> std::string_view;

  auto set_content(PageContentView) -> Response&;

  auto set_content_type(Content) -> Response&;

 private:
  Status                                       _status;
  std::unordered_map<Header, std::string_view> _headers;
  PageContentView                              _page;
  std::string                                  _content_length;

  auto total_length() const -> size_t;

  inline void        build_add_response_line(ByteVector&) const;
  static inline void build_add_header(Header, std::string_view, ByteVector&);
  static inline void build_add_content(PageContentView, ByteVector&);
};
}  // namespace simple::http

#endif