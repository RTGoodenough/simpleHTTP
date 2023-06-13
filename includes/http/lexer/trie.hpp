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

#include <http/lexer/token.hpp>

namespace simple {

constexpr int ALPHABET_LENGTH = 26;
constexpr int DICT_SIZE = 38;

struct TrieEntry {
  TokenType   type;
  std::string str;
};

static const std::vector<TrieEntry>& getReservedWords() {
  static const std::vector<TrieEntry> ENTRIES{
      {TokenType::METHOD, "CONNECT"},
      {TokenType::METHOD, "DELETE"},
      {TokenType::METHOD, "GET"},
      {TokenType::METHOD, "HEAD"},
      {TokenType::METHOD, "OPTIONS"},
      {TokenType::METHOD, "POST"},
      {TokenType::METHOD, "PUT"},
      {TokenType::METHOD, "TRACE"},
      {TokenType::HEADER, "A-IM"},
      {TokenType::HEADER, "Accept-Ch"},
      {TokenType::HEADER, "Accept-Charset"},
      {TokenType::HEADER, "Accept-Datetime"},
      {TokenType::HEADER, "Accept-Encoding"},
      {TokenType::HEADER, "Accept-Language"},
      {TokenType::HEADER, "Accept-Patch"},
      {TokenType::HEADER, "Accept-Ranges"},
      {TokenType::HEADER, "Accept"},
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
      {TokenType::HEADER, "Connection"},
      {TokenType::HEADER, "Content-Disposition"},
      {TokenType::HEADER, "Content-Encoding"},
      {TokenType::HEADER, "Content-Language"},
      {TokenType::HEADER, "Content-Length"},
      {TokenType::HEADER, "Content-Location"},
      {TokenType::HEADER, "Content-Md5"},
      {TokenType::HEADER, "Content-Range"},
      {TokenType::HEADER, "Content-Type"},
      {TokenType::HEADER, "Cookie"},
      {TokenType::HEADER, "Date"},
      {TokenType::HEADER, "Delta-Base"},
      {TokenType::HEADER, "Etag"},
      {TokenType::HEADER, "Expect"},
      {TokenType::HEADER, "Expires"},
      {TokenType::HEADER, "Forwarded"},
      {TokenType::HEADER, "From"},
      {TokenType::HEADER, "Host"},
      {TokenType::HEADER, "If-Match"},
      {TokenType::HEADER, "If-Modified-Since"},
      {TokenType::HEADER, "If-None-Match"},
      {TokenType::HEADER, "If-Range"},
      {TokenType::HEADER, "If-Unmodified-Since"},
      {TokenType::HEADER, "Im"},
      {TokenType::HEADER, "Last"},
      {TokenType::HEADER, "Link"},
      {TokenType::HEADER, "Max-Forwards"},
      {TokenType::HEADER, "Origin"},
      {TokenType::HEADER, "P3p"},
      {TokenType::HEADER, "Pragma"},
      {TokenType::HEADER, "Preference-Applied"},
      {TokenType::HEADER, "Proxy-Authenticate"},
      {TokenType::HEADER, "Proxy-Authorization"},
      {TokenType::HEADER, "Public-Key-Pins"},
      {TokenType::HEADER, "Range"},
      {TokenType::HEADER, "Referer"},
      {TokenType::HEADER, "Retry-After"},
      {TokenType::HEADER, "Server"},
      {TokenType::HEADER, "Set-Cookie"},
      {TokenType::HEADER, "Strict-Transport-Security"},
      {TokenType::HEADER, "TE"},
      {TokenType::HEADER, "Tk"},
      {TokenType::HEADER, "Trailer"},
      {TokenType::HEADER, "Transfer-Encoding"},
      {TokenType::HEADER, "Upgrade"},
      {TokenType::HEADER, "User-Agent"},
      {TokenType::HEADER, "Vary"},
      {TokenType::HEADER, "Via"},
      {TokenType::HEADER, "Warning"},
      {TokenType::HEADER, "WWW-Authenticate"},
      {TokenType::HEADER, "X-Frame-Options"},
      {TokenType::VERSION, "HTTP/1.0"},
      {TokenType::VERSION, "HTTP/1.1"},
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
    for (const auto& entry : getReservedWords()) {
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

  [[nodiscard]] Token traverse(const char*& str, const char* const end) const {
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
        return completeID(start, str, end);
      }

      curr = next;
      ++str;
    }

    return {TokenType::ID, std::string_view(start, std::distance(start, str))};
  }

 private:
  std::vector<TrieNode> _arena;
  TrieNode*             _root;

  static inline size_t index(char chr) {
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

  [[nodiscard]] static Token completeID(const char* start, const char*& str,
                                        const char* const end) {
    while (str < end &&
           (std::isalpha(*str) || *str == '.' || *str == '-' || *str == '_')) {
      ++str;
    }
    return {TokenType::ID, std::string_view(start, std::distance(start, str))};
  }
};
}  // namespace simple

#endif  // SIMPLE_HTTP_HTTPTRIE_HPP