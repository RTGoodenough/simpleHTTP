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

#include <iterator>
#include <optional>
#include <stdexcept>
#include <string_view>

#include "http/lexer/token.hpp"
#include "http/parsing.hpp"
#include "http/types/header.types.hpp"
#include "http/types/http.types.hpp"
#include "http/types/request.hpp"
#include "logging/logging.hpp"
#include "util/string_view_manipulations.hpp"

namespace simple::http {

auto Parser::parse(std::string_view reqStr) -> std::optional<Request> {
  _req = http::Request();
  _lexer = Lexer(reqStr);
  next_token();

  debug("Method");
  if (!method()) return std::nullopt;
  debug("uri");
  if (!uri()) return std::nullopt;
  debug("version");
  if (!version()) return std::nullopt;
  if (!match(TokenType::LINE_END)) return std::nullopt;
  debug("headers");
  if (!headers()) return std::nullopt;

  if (!_lookahead.is_type(TokenType::LINE_END)) return std::nullopt;

  debug("Content");
  _req.set_content(_lexer.content());

  if (_req.get_header(Header::HOST).empty()) return std::nullopt;
  _req.set_target_host(_req.get_header(Header::HOST));

  debug("return");
  return _req;
}

auto Parser::match(TokenType type) -> bool {
  if (!_lookahead.is_type(type)) {
    return false;
  }
  next_token();
  return true;
}

void Parser::next_token() {
  _token = _lookahead;
  _lookahead = _lexer.next_token();
}

auto Parser::method() -> bool {
  if (!match(TokenType::METHOD)) return false;
  _req.set_method(method_from_str(_token.value));
  return true;
}

auto Parser::version() -> bool {
  if (!match(TokenType::VERSION)) return false;
  _req.set_version(_token.value);
  return _req.get_verion() != http::Version::INVALID;
}

auto Parser::uri() -> bool {
  if (_lookahead.is_type(TokenType::SCHEME)) {
    auto aform = absolute_form();
    if (aform) {
      _req.set_uri(aform.value());
      _req.set_uri_form(UriForm::ABSOLUTE);
      return true;
    }
    return false;
  }

  if (_lookahead.is_type(TokenType::FSLASH)) {
    auto oform = origin_form();
    if (oform) {
      _req.set_uri(oform.value());
      _req.set_uri_form(UriForm::ORIGIN);
      return true;
    }
    return false;
  }

  if (_lookahead.is_type(TokenType::ID)) {
    auto auform = authority_form();
    if (auform) {
      _req.set_uri(auform.value());
      _req.set_uri_form(UriForm::AUTHORITY);
      return true;
    }
  }

  auto asform = asterisk_form();
  if (asform) {
    _req.set_uri(asform.value());
    _req.set_uri_form(UriForm::ASTERISK);
    return true;
  }

  return false;
}

auto Parser::headers() -> bool {
  while (_lookahead.type != TokenType::LINE_END) {
    if (!match(TokenType::HEADER)) return false;
    std::string_view temp = _token.value;
    if (!match(TokenType::COLON)) return false;
    std::string_view hdrVal = _lexer.next_line().value;
    _req.set_header(
        header_from_str(temp),
        std::string_view(_lookahead.value.begin(), std::distance(_lookahead.value.begin(), hdrVal.end())));
    next_token();
    if (!match(TokenType::LINE_END)) return false;
  }

  return true;
}

auto Parser::query() -> bool {
  // TODO (rolland) : fully parse query, currently just accepts everything into a string_view
  if (_lookahead.type != TokenType::QUESTION) return true;
  next_token();
  const char* begin = _token.value.end() + 1;
  const char* end = nullptr;

  while (_lookahead.is_type(TokenType::ID) || _lookahead.is_type(TokenType::AMPER) ||
         _lookahead.is_type(TokenType::EQ)) {
    next_token();
  }
  end = _lookahead.value.begin();

  _req.set_query(std::string_view(begin, std::distance(begin, end - 1)));

  return true;
}

auto Parser::origin_form() -> std::optional<http::UriTarget> {
  const char* begin = _token.value.end() + 1;
  const char* end = nullptr;
  while (_lookahead.is_type(TokenType::ID) || _lookahead.is_type(TokenType::FSLASH)) {
    next_token();
  }
  end = _lookahead.value.begin();
  if (!query()) return std::nullopt;

  return http::UriTarget{Scheme::HTTP, std::string_view{},
                         std::string_view(begin, std::distance(begin, end - 1)), "80"};
}

auto Parser::absolute_form() -> std::optional<http::UriTarget> {
  //TODO(rolland) this
  throw std::runtime_error("absolute form not implemented");
  return std::nullopt;
}

auto Parser::authority_form() -> std::optional<http::UriTarget> {
  //TODO(rolland) this
  throw std::runtime_error("authority not implemented");
  return std::nullopt;
}

auto Parser::asterisk_form() -> std::optional<http::UriTarget> {
  if (!match(TokenType::ASTERISK)) return std::nullopt;
  return http::UriTarget{Scheme::HTTP, {}, "*", {}};
}

}  // namespace simple::http