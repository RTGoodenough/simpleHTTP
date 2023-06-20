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
  [[nodiscard]] std::optional<http::Request> parse(std::string_view);

 private:
  Lexer   _lexer;
  Token   _token;
  Token   _lookahead;
  Request _req;

  [[nodiscard]] bool match(TokenType);
  void               nextToken();

  [[nodiscard]] bool method();
  [[nodiscard]] bool uri();
  [[nodiscard]] bool headers();
  [[nodiscard]] bool version();
  [[nodiscard]] bool query();

  [[nodiscard]] std::optional<http::UriTarget> originForm();
  [[nodiscard]] std::optional<http::UriTarget> absoluteForm();
  [[nodiscard]] std::optional<http::UriTarget> authorityForm();
  [[nodiscard]] std::optional<http::UriTarget> asteriskForm();
};

}  // namespace simple::http

#endif