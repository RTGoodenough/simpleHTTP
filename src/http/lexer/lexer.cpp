
#include <cctype>
#include <iterator>
#include <string>
#include <string_view>

#include <http/lexer/lexer.hpp>
#include <http/lexer/token.hpp>
#include <http/lexer/trie.hpp>

#include <logging/logging.hpp>

namespace simple {

inline const OpTrie& getTrie() {
  static const OpTrie TRIE{};
  return TRIE;
}

Token Lexer::nextToken() {
  while (_iter != _data.end()) {
    skipWhiteSpace();
    switch (*_iter) {
      case '\r':
        return newLine();
        break;
      case ',':
        ++_iter;
        return {TokenType::COMMA, std::string_view{}};
      case '.':
        ++_iter;
        return {TokenType::PERIOD, std::string_view{}};
      case '!':
        ++_iter;
        return {TokenType::EXLAIM, std::string_view{}};
      case '\"':
        ++_iter;
        return {TokenType::DQUOTE, std::string_view{}};
      case '#':
        ++_iter;
        return {TokenType::POUND, std::string_view{}};
      case '$':
        ++_iter;
        return {TokenType::DOLLAR, std::string_view{}};
      case '%':
        ++_iter;
        return {TokenType::PERCENT, std::string_view{}};
      case '&':
        ++_iter;
        return {TokenType::AMPER, std::string_view{}};
      case '\'':
        ++_iter;
        return {TokenType::SQUOTE, std::string_view{}};
      case '`':
        ++_iter;
        return {TokenType::BTICK, std::string_view{}};
      case '(':
        ++_iter;
        return {TokenType::LPAREN, std::string_view{}};
      case ')':
        ++_iter;
        return {TokenType::RPAREN, std::string_view{}};
      case '*':
        ++_iter;
        return {TokenType::ASTERISK, std::string_view{}};
      case '+':
        ++_iter;
        return {TokenType::PLUS, std::string_view{}};
      case '-':
        ++_iter;
        return {TokenType::MINUS, std::string_view{}};
      case '/':
        ++_iter;
        return {TokenType::FSLASH, std::string_view{}};
      case ';':
        ++_iter;
        return {TokenType::SEMICOLON, std::string_view{}};
      case '>':
        ++_iter;
        return {TokenType::GT, std::string_view{}};
      case '<':
        ++_iter;
        return {TokenType::LT, std::string_view{}};
      case '=':
        ++_iter;
        return {TokenType::EQ, std::string_view{}};
      case '?':
        ++_iter;
        return {TokenType::QUESTION, std::string_view{}};
      case '@':
        ++_iter;
        return {TokenType::AT, std::string_view{}};
      case '[':
        ++_iter;
        return {TokenType::LBRACKET, std::string_view{}};
      case ']':
        ++_iter;
        return {TokenType::RBRACKET, std::string_view{}};
      case '\\':
        ++_iter;
        return {TokenType::BSLASH, std::string_view{}};
      case '^':
        ++_iter;
        return {TokenType::CARROT, std::string_view{}};
      case '_':
        ++_iter;
        return {TokenType::UNDER, std::string_view{}};
      case '|':
        ++_iter;
        return {TokenType::PIPE, std::string_view{}};
      case '~':
        ++_iter;
        return {TokenType::TILDE, std::string_view{}};
      case ':':
        ++_iter;
        return {TokenType::COLON, std::string_view{}};
      default:
        break;
    }

    if (isalpha(*_iter)) {
      return parseString();
    }

    if (isdigit(*_iter)) {
      return parseNumber();
    }

    Token ret = {TokenType::CHAR, {_iter, 1}};
    ++_iter;
    return ret;
  }

  return Token{TokenType::END, {}};
}

Token Lexer::nextLine() {
  skipWhiteSpace();
  const char* start = _iter;
  while (_iter != _data.end()) {
    if (*_iter == '\r') {
      ++_iter;
      if (*_iter == '\n') {
        _iter -= 1;
        break;
      }
    }
    ++_iter;
  }

  return {TokenType::ID, std::string_view(start, std::distance(start, _iter))};
}

Token Lexer::parseString() {
  auto val = getTrie().traverse(_iter, _data.end());
  return val;
}

Token Lexer::parseNumber() {
  const auto* start = _iter;
  while (std::isdigit(*_iter) || *_iter == '.') {
    ++_iter;
  }
  return {TokenType::NUMBER, std::string_view(start, std::distance(start, _iter))};
}

Token Lexer::newLine() {
  ++_iter;

  if (_iter == _data.end()) {
    return {TokenType::RETURN, {}};
  }

  if (*_iter == '\n') {
    ++_iter;
    return {TokenType::LINE_END, {}};
  }

  return {TokenType::RETURN, {}};
}

void Lexer::skipWhiteSpace() {
  while (*_iter == ' ') {
    ++_iter;
  }
}

std::string_view Lexer::content() {
  return {_iter, static_cast<size_t>(std::distance(_iter, _data.end()))};
}

// ------------------------------------ CONSTRUCTORS ------------------------------------------------------

Lexer::Lexer(std::string_view req) : _data(req), _iter(req.begin()) {}

Lexer::Lexer(const Lexer& other) noexcept : _data(other._data), _iter(_data.begin()) {}

Lexer::Lexer(Lexer&& other) noexcept : _data(other._data), _iter(_data.begin()) {}

Lexer& Lexer::operator=(const Lexer& other) noexcept {
  if (this == &other) {
    return *this;
  }

  _data = other._data;
  _iter = _data.begin();
  return *this;
}

Lexer& Lexer::operator=(Lexer&& other) noexcept {
  _data = other._data;
  _iter = _data.begin();
  return *this;
}
}  // namespace simple
