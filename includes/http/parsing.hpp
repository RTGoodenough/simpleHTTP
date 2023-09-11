/**
 * @file parsing.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <optional>
#include <string_view>

#include <http/lexer/lexer.hpp>
#include <http/types/request.hpp>
#include <http/types/status.types.hpp>

namespace simple::http {

class Parser {
 public:
  [[nodiscard]] auto parse(std::string_view) -> std::optional<http::Request>;

 private:
  Lexer   _lexer;
  Token   _token;
  Token   _lookahead;
  Request _req;

  [[nodiscard]] auto match(TokenType) -> bool;
  void               nextToken();

  [[nodiscard]] auto method() -> bool;
  [[nodiscard]] auto uri() -> bool;
  [[nodiscard]] auto headers() -> bool;
  [[nodiscard]] auto version() -> bool;
  [[nodiscard]] auto query() -> bool;

  [[nodiscard]] auto originForm() -> std::optional<http::UriTarget>;
  [[nodiscard]] auto absoluteForm() -> std::optional<http::UriTarget>;
  [[nodiscard]] auto authorityForm() -> std::optional<http::UriTarget>;
  [[nodiscard]] auto asteriskForm() -> std::optional<http::UriTarget>;
};

}  // namespace simple::http

#endif