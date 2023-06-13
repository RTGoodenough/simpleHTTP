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
  Request _req;

  bool match(TokenType);
  void nextToken();

  bool method();
  bool uri();
  bool header();

  std::optional<http::Uri> originForm();
  std::optional<http::Uri> absoluteForm();
  std::optional<http::Uri> authorityForm();
  std::optional<http::Uri> asteriskForm();
};

}  // namespace simple::http

#endif