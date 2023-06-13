/**
 * @file parsing.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <http/lexer/token.hpp>
#include <http/parsing.hpp>
#include <http/types/http.types.hpp>
#include <optional>
#include <util/string_view_manipulations.hpp>

namespace simple::http {

std::optional<Request> Parser::parse(std::string_view reqStr) {
  Lexer lexer(reqStr);

  if (!method()) return std::nullopt;
  match(TokenType::LINE_END);
  if (!uri()) return std::nullopt;
  match(TokenType::LINE_END);
  if (!header()) return std::nullopt;
  match(TokenType::LINE_END);
  _req.setContent(_lexer.content());
  return std::nullopt;
}

bool Parser::match(TokenType type) {
  _token = _lexer.nextToken();
  return _token.type == type;
}

void Parser::nextToken() { _token = _lexer.nextToken(); }

bool Parser::method() {
  if (!match(TokenType::METHOD)) return false;
  _req.setMethod(methodFromStr(_token.value));
  return true;
}

bool Parser::uri() {
  auto oform = originForm();
  if (oform) {
    _req.setUri(oform.value());
    return true;
  }

  auto aform = absoluteForm();
  if (aform) {
    _req.setUri(aform.value());
    return true;
  }

  auto auform = authorityForm();
  if (auform) {
    _req.setUri(auform.value());
    return true;
  }

  auto asform = asteriskForm();
  if (asform) {
    _req.setUri(asform.value());
    return true;
  }

  return false;
}

bool Parser::header() {}

std::optional<http::Uri> Parser::originForm() {
  //TODO(rolland) this
}

std::optional<http::Uri> Parser::absoluteForm() {
  //TODO(rolland) this
}

std::optional<http::Uri> Parser::authorityForm() {
  //TODO(rolland) this
}

std::optional<http::Uri> Parser::asteriskForm() {
  //TODO(rolland) this
}

}  // namespace simple::http