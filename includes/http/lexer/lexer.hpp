/**
 * @file lexer.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

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

  [[nodiscard]] auto next_token() -> Token;
  [[nodiscard]] auto next_line() -> Token;
  [[nodiscard]] auto content() -> std::string_view;
  [[nodiscard]] auto expect_status() -> std::optional<Token>;

 private:
  std::string_view           _data;
  std::string_view::iterator _iter{};

  void               skip_white_space();
  [[nodiscard]] auto parse_string() -> Token;
  [[nodiscard]] auto parse_number() -> Token;
  [[nodiscard]] auto new_line() -> Token;
};
}  // namespace simple

#endif