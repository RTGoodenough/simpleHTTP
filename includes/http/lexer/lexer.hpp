#ifndef SIMPLE_HTTP_LEXER_HPP
#define SIMPLE_HTTP_LEXER_HPP

#include <optional>
#include <string_view>

#include <http/lexer/token.hpp>
#include <http/lexer/trie.hpp>

namespace simple {
class Lexer {
 public:
  explicit Lexer(std::string_view);
  Lexer() = default;
  ~Lexer() = default;
  Lexer(const Lexer&) noexcept;
  Lexer(Lexer&&) noexcept;
  Lexer& operator=(const Lexer&) noexcept;
  Lexer& operator=(Lexer&&) noexcept;

  [[nodiscard]] Token                nextToken();
  [[nodiscard]] Token                nextLine();
  [[nodiscard]] std::string_view     content();
  [[nodiscard]] std::optional<Token> expectStatus();

 private:
  std::string_view           _data;
  std::string_view::iterator _iter{};

  void                skipWhiteSpace();
  [[nodiscard]] Token parseString();
  [[nodiscard]] Token parseNumber();
  [[nodiscard]] Token newLine();
};
}  // namespace simple

#endif