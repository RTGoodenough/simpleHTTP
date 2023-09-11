#ifndef SIMPLE_HTTP_LEXER_HPP
#define SIMPLE_HTTP_LEXER_HPP

#include <optional>
#include <string_view>

#include "http/lexer/token.hpp"
#include "http/lexer/trie.hpp"

namespace simple {
class Lexer {
 public:
  explicit Lexer(std::string_view);
  Lexer() = default;
  ~Lexer() = default;
  Lexer(const Lexer&) noexcept;
  Lexer(Lexer&&) noexcept;
  auto operator=(const Lexer&) noexcept -> Lexer&;
  auto operator=(Lexer&&) noexcept -> Lexer&;

  [[nodiscard]] auto nextToken() -> Token;
  [[nodiscard]] auto nextLine() -> Token;
  [[nodiscard]] auto content() -> std::string_view;
  [[nodiscard]] auto expectStatus() -> std::optional<Token>;

 private:
  std::string_view           _data;
  std::string_view::iterator _iter{};

  void               skipWhiteSpace();
  [[nodiscard]] auto parseString() -> Token;
  [[nodiscard]] auto parseNumber() -> Token;
  [[nodiscard]] auto newLine() -> Token;
};
}  // namespace simple

#endif