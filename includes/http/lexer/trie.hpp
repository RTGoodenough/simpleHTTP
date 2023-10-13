/**
 * @file trie.hpp
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

#ifndef SIMPLE_HTTP_HTTPTRIE_HPP
#define SIMPLE_HTTP_HTTPTRIE_HPP

#include <iostream>

#include <array>
#include <cctype>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "http/lexer/token.hpp"

namespace simple {

constexpr int ALPHABET_LENGTH = 26;
constexpr int DICT_SIZE = 39;

struct TrieEntry {
  TokenType   type;
  std::string str;
};

// TODO(rolland): need to add headers for sec-ch-ua etc. or handle unknown headers
static auto get_reserved_words() -> const std::vector<TrieEntry>& {
  static const std::vector<TrieEntry> ENTRIES{
      {TokenType::METHOD, "CONNECT"},
      {TokenType::METHOD, "DELETE"},
      {TokenType::METHOD, "GET"},
      {TokenType::METHOD, "HEAD"},
      {TokenType::METHOD, "OPTIONS"},
      {TokenType::METHOD, "POST"},
      {TokenType::METHOD, "PUT"},
      {TokenType::METHOD, "TRACE"},
      {TokenType::HEADER, "Accept"},
      {TokenType::HEADER, "Accept-CH"},
      {TokenType::HEADER, "Accept-CH-Lifetime"},
      {TokenType::HEADER, "Non-standardDeprecated"},
      {TokenType::HEADER, "Accept-Charset"},
      {TokenType::HEADER, "Accept-Encoding"},
      {TokenType::HEADER, "Accept-Language"},
      {TokenType::HEADER, "Accept-Patch"},
      {TokenType::HEADER, "Accept-Post"},
      {TokenType::HEADER, "Accept-Ranges"},
      {TokenType::HEADER, "Access-Control-Allow-Credentials"},
      {TokenType::HEADER, "Access-Control-Allow-Headers"},
      {TokenType::HEADER, "Access-Control-Allow-Methods"},
      {TokenType::HEADER, "Access-Control-Allow-Origin"},
      {TokenType::HEADER, "Access-Control-Expose-Headers"},
      {TokenType::HEADER, "Access-Control-Max-Age"},
      {TokenType::HEADER, "Access-Control-Request-Headers"},
      {TokenType::HEADER, "Access-Control-Request-Method"},
      {TokenType::HEADER, "Age"},
      {TokenType::HEADER, "Allow"},
      {TokenType::HEADER, "Alt-Svc"},
      {TokenType::HEADER, "Authorization"},
      {TokenType::HEADER, "Cache-Control"},
      {TokenType::HEADER, "Clear-Site-Data"},
      {TokenType::HEADER, "Connection"},
      {TokenType::HEADER, "Content-Disposition"},
      {TokenType::HEADER, "Content-DPR"},
      {TokenType::HEADER, "Non-standardDeprecated"},
      {TokenType::HEADER, "Content-Encoding"},
      {TokenType::HEADER, "Content-Language"},
      {TokenType::HEADER, "Content-Length"},
      {TokenType::HEADER, "Content-Location"},
      {TokenType::HEADER, "Content-Range"},
      {TokenType::HEADER, "Content-Security-Policy"},
      {TokenType::HEADER, "Content-Security-Policy-Report-Only"},
      {TokenType::HEADER, "Content-Type"},
      {TokenType::HEADER, "Cookie"},
      {TokenType::HEADER, "Critical-CH"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Cross-Origin-Embedder-Policy"},
      {TokenType::HEADER, "Cross-Origin-Opener-Policy"},
      {TokenType::HEADER, "Cross-Origin-Resource-Policy"},
      {TokenType::HEADER, "Date"},
      {TokenType::HEADER, "Device-Memory"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Digest"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "DNT"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "Downlink"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "DPR"},
      {TokenType::HEADER, "Non-standardDeprecated"},
      {TokenType::HEADER, "Early-Data"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "ECT"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "ETag"},
      {TokenType::HEADER, "Expect"},
      {TokenType::HEADER, "Expect-CT"},
      {TokenType::HEADER, "Expires"},
      {TokenType::HEADER, "Forwarded"},
      {TokenType::HEADER, "From"},
      {TokenType::HEADER, "Host"},
      {TokenType::HEADER, "If-Match"},
      {TokenType::HEADER, "If-Modified-Since"},
      {TokenType::HEADER, "If-None-Match"},
      {TokenType::HEADER, "If-Range"},
      {TokenType::HEADER, "If-Unmodified-Since"},
      {TokenType::HEADER, "Keep-Alive"},
      {TokenType::HEADER, "Large-Allocation"},
      {TokenType::HEADER, "Non-standardDeprecated"},
      {TokenType::HEADER, "Last-Modified"},
      {TokenType::HEADER, "Link"},
      {TokenType::HEADER, "Location"},
      {TokenType::HEADER, "Max-Forwards"},
      {TokenType::HEADER, "NEL"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Origin"},
      {TokenType::HEADER, "Permissions-Policy"},
      {TokenType::HEADER, "Pragma"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "Proxy-Authenticate"},
      {TokenType::HEADER, "Proxy-Authorization"},
      {TokenType::HEADER, "Range"},
      {TokenType::HEADER, "Referer"},
      {TokenType::HEADER, "Referrer-Policy"},
      {TokenType::HEADER, "Retry-After"},
      {TokenType::HEADER, "RTT"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Save-Data"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-Prefers-Reduced-Motion"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Arch"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Bitness"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Full-Version"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "Sec-CH-UA-Full-Version-List"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Mobile"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Model"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Platform"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-CH-UA-Platform-Version"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-Fetch-Dest"},
      {TokenType::HEADER, "Sec-Fetch-Mode"},
      {TokenType::HEADER, "Sec-Fetch-Site"},
      {TokenType::HEADER, "Sec-Fetch-User"},
      {TokenType::HEADER, "Sec-GPC"},
      {TokenType::HEADER, "Experimental"},
      {TokenType::HEADER, "Sec-Purpose"},
      {TokenType::HEADER, "Purpose"},
      {TokenType::HEADER, "Sec-WebSocket-Accept"},
      {TokenType::HEADER, "Server"},
      {TokenType::HEADER, "Server-Timing"},
      {TokenType::HEADER, "Service-Worker-Navigation-Preload"},
      {TokenType::HEADER, "Set-Cookie"},
      {TokenType::HEADER, "SourceMap"},
      {TokenType::HEADER, "Strict-Transport-Security"},
      {TokenType::HEADER, "TE"},
      {TokenType::HEADER, "Timing-Allow-Origin"},
      {TokenType::HEADER, "Tk"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "Trailer"},
      {TokenType::HEADER, "Transfer-Encoding"},
      {TokenType::HEADER, "Upgrade"},
      {TokenType::HEADER, "Upgrade-Insecure-Requests"},
      {TokenType::HEADER, "User-Agent"},
      {TokenType::HEADER, "Vary"},
      {TokenType::HEADER, "Via"},
      {TokenType::HEADER, "Viewport-Width"},
      {TokenType::HEADER, "Non-standardDeprecated"},
      {TokenType::HEADER, "Want-Digest"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "Warning"},
      {TokenType::HEADER, "Deprecated"},
      {TokenType::HEADER, "Width"},
      {TokenType::HEADER, "Non-standardDeprecated"},
      {TokenType::HEADER, "WWW-Authenticate"},
      {TokenType::HEADER, "X-Content-Type-Options"},
      {TokenType::HEADER, "X-DNS-Prefetch-Control"},
      {TokenType::HEADER, "Non-standard"},
      {TokenType::HEADER, "X-Forwarded-For"},
      {TokenType::HEADER, "Non-standard"},
      {TokenType::HEADER, "X-Forwarded-Host"},
      {TokenType::HEADER, "Non-standard"},
      {TokenType::HEADER, "X-Forwarded-Proto"},
      {TokenType::HEADER, "Non-standard"},
      {TokenType::HEADER, "X-Frame-Options"},
      {TokenType::HEADER, "X-XSS-Protection"},
      {TokenType::VERSION, "HTTP/1.0"},
      {TokenType::VERSION, "HTTP/1.1"},
      {TokenType::SCHEME, "http"},
      {TokenType::SCHEME, "https"},
  };

  return ENTRIES;
}

struct TrieNode {
  TokenType                        type = TokenType::ID;
  std::array<TrieNode*, DICT_SIZE> next{};
};

class OpTrie {
 public:
  OpTrie() : _arena(1), _root(&_arena.back()) {
    for (const auto& entry : get_reserved_words()) {
      add(entry.str, entry.type);
    }
  }

  void add(const std::string& str, TokenType type) {
    TrieNode* curr = _root;
    for (char chr : str) {
      size_t    idx = index(chr);
      TrieNode* temp = curr->next.at(idx);
      if (temp == nullptr) {
        // NOLINTNEXTLINE
        temp = new TrieNode();
        curr->next.at(idx) = temp;
      }
      curr = temp;
    }

    curr->type = type;
  }

  [[nodiscard]] auto traverse(const char*& str, const char* const end) const -> Token {
    TrieNode*   curr = _root;
    const char* start = str;

    while (str < end) {
      size_t idx = index(*str);

      if (*str == ' ') {
        return {curr->type, std::string_view(start, std::distance(start, str))};
      }

      if (idx >= DICT_SIZE) {
        break;
      }

      TrieNode* next = curr->next.at(idx);
      if (next == nullptr) {
        return complete_id(start, str, end);
      }

      curr = next;
      ++str;
    }

    return {curr->type, std::string_view(start, std::distance(start, str))};
  }

 private:
  std::vector<TrieNode> _arena;
  TrieNode*             _root;

  static inline auto index(char chr) -> size_t {
    size_t idx = std::tolower(chr) - 'a';
    // NOLINTBEGIN (cppcoreguidelines-avoid-magic-numbers)
    if (idx >= ALPHABET_LENGTH) {
      switch (chr) {
        case '-':
          idx = ALPHABET_LENGTH;
          break;
        case '0':
          idx = ALPHABET_LENGTH + 1;
          break;
        case '1':
          idx = ALPHABET_LENGTH + 2;
          break;
        case '2':
          idx = ALPHABET_LENGTH + 3;
          break;
        case '3':
          idx = ALPHABET_LENGTH + 4;
          break;
        case '4':
          idx = ALPHABET_LENGTH + 5;
          break;
        case '5':
          idx = ALPHABET_LENGTH + 6;
          break;
        case '6':
          idx = ALPHABET_LENGTH + 7;
          break;
        case '7':
          idx = ALPHABET_LENGTH + 8;
          break;
        case '8':
          idx = ALPHABET_LENGTH + 9;
          break;
        case '9':
          idx = ALPHABET_LENGTH + 10;
          break;
        case '/':
          idx = ALPHABET_LENGTH + 11;
          break;
        case '.':
          idx = ALPHABET_LENGTH + 12;
          break;
        default:
          return std::numeric_limits<size_t>::max();
      }
      // NOLINTEND
    }
    return idx;
  }

  [[nodiscard]] static auto complete_id(const char* start, const char*& str, const char* const end) -> Token {
    while (str < end && (std::isalpha(*str) || *str == '.' || *str == '-' || *str == '_')) {
      ++str;
    }
    return {TokenType::ID, std::string_view(start, std::distance(start, str))};
  }
};
}  // namespace simple

#endif  // SIMPLE_HTTP_HTTPTRIE_HPP