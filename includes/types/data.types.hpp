#ifndef YASUMI_DATA_TYPES_HPP
#define YASUMI_DATA_TYPES_HPP

#include <vector>

namespace simpleHTTP {
typedef std::vector<char> ByteVector;

enum class Content {
  INVALID,
  NOT_FOUND,
  BAD_REQUEST,
  HTML,
  JAVASCRIPT,
};

struct File {
  const char* content = nullptr;
  size_t      length = 0;
};
}  // namespace simpleHTTP

#endif