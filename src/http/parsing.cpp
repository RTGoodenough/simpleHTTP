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

#include <http/lexer/token.hpp>
#include <http/parsing.hpp>
#include <http/types/header.types.hpp>
#include <http/types/http.types.hpp>
#include <http/types/request.hpp>
#include <logging/logging.hpp>
#include <util/string_view_manipulations.hpp>

namespace simple::http {

auto Parser::parse(std::string_view reqStr) -> std::optional<Request> {
  _req = http::Request();
  _lexer = Lexer(reqStr);
  nextToken();

  debug("Method");
  if (!method()) return std::nullopt;
  debug("uri");
  if (!uri()) return std::nullopt;
  debug("version");
  if (!version()) return std::nullopt;
  if (!match(TokenType::LINE_END)) return std::nullopt;
  debug("headers");
  if (!headers()) return std::nullopt;

  if (!_lookahead.isType(TokenType::LINE_END)) return std::nullopt;

  debug("Content");
  _req.setContent(_lexer.content());

  if (_req.getHeader(Header::HOST).empty()) return std::nullopt;
  _req.setTargetHost(_req.getHeader(Header::HOST));

  debug("return");
  return _req;
}

auto Parser::match(TokenType type) -> bool {
  if (!_lookahead.isType(type)) {
    return false;
  }
  nextToken();
  return true;
}

void Parser::nextToken() {
  _token = _lookahead;
  _lookahead = _lexer.nextToken();
}

auto Parser::method() -> bool {
  if (!match(TokenType::METHOD)) return false;
  _req.setMethod(methodFromStr(_token.value));
  return true;
}

auto Parser::version() -> bool {
  if (!match(TokenType::VERSION)) return false;
  _req.setVersion(_token.value);
  return _req.getVerion() != http::Version::INVALID;
}

auto Parser::uri() -> bool {
  if (_lookahead.isType(TokenType::SCHEME)) {
    auto aform = absoluteForm();
    if (aform) {
      _req.setUri(aform.value());
      _req.setUriForm(UriForm::ABSOLUTE);
      return true;
    }
    return false;
  }

  if (_lookahead.isType(TokenType::FSLASH)) {
    auto oform = originForm();
    if (oform) {
      _req.setUri(oform.value());
      _req.setUriForm(UriForm::ORIGIN);
      return true;
    }
    return false;
  }

  if (_lookahead.isType(TokenType::ID)) {
    auto auform = authorityForm();
    if (auform) {
      _req.setUri(auform.value());
      _req.setUriForm(UriForm::AUTHORITY);
      return true;
    }
  }

  auto asform = asteriskForm();
  if (asform) {
    _req.setUri(asform.value());
    _req.setUriForm(UriForm::ASTERISK);
    return true;
  }

  return false;
}

auto Parser::headers() -> bool {
  while (_lookahead.type != TokenType::LINE_END) {
    if (!match(TokenType::HEADER)) return false;
    std::string_view temp = _token.value;
    if (!match(TokenType::COLON)) return false;
    std::string_view hdrVal = _lexer.nextLine().value;
    _req.setHeader(
        headerFromStr(temp),
        std::string_view(_lookahead.value.begin(), std::distance(_lookahead.value.begin(), hdrVal.end())));
    nextToken();
    if (!match(TokenType::LINE_END)) return false;
  }

  return true;
}

auto Parser::query() -> bool {
  // TODO (rolland) : fully parse query, currently just accepts everything into a string_view
  if (_lookahead.type != TokenType::QUESTION) return true;
  nextToken();
  const char* begin = _token.value.end() + 1;
  const char* end = nullptr;

  while (_lookahead.isType(TokenType::ID) || _lookahead.isType(TokenType::AMPER) ||
         _lookahead.isType(TokenType::EQ)) {
    nextToken();
  }
  end = _lookahead.value.begin();

  _req.setQuery(std::string_view(begin, std::distance(begin, end - 1)));

  return true;
}

auto Parser::originForm() -> std::optional<http::UriTarget> {
  const char* begin = _token.value.end() + 1;
  const char* end = nullptr;
  while (_lookahead.isType(TokenType::ID) || _lookahead.isType(TokenType::FSLASH)) {
    nextToken();
  }
  end = _lookahead.value.begin();
  if (!query()) return std::nullopt;

  return http::UriTarget{Scheme::HTTP, std::string_view{},
                         std::string_view(begin, std::distance(begin, end - 1)), "80"};
}

auto Parser::absoluteForm() -> std::optional<http::UriTarget> {
  //TODO(rolland) this
  throw std::runtime_error("absolute form not implemented");
  return std::nullopt;
}

auto Parser::authorityForm() -> std::optional<http::UriTarget> {
  //TODO(rolland) this
  throw std::runtime_error("authority not implemented");
  return std::nullopt;
}

auto Parser::asteriskForm() -> std::optional<http::UriTarget> {
  if (!match(TokenType::ASTERISK)) return std::nullopt;
  return http::UriTarget{Scheme::HTTP, {}, "*", {}};
}

}  // namespace simple::http