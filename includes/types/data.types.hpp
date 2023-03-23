#ifndef YASUMI_DATA_TYPES_HPP
#define YASUMI_DATA_TYPES_HPP

#include <vector>

namespace simpleHTTP {
typedef std::vector<char> ByteVector;

enum ContentType {
  INVALID,
  HTML,
  JAVASCRIPT,
};

struct File {
  const char* content;
  size_t      length;
};
}  // namespace simpleHTTP

#endif