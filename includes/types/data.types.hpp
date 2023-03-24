/**
 * @file data.types.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_DATA_TYPES_HPP
#define SIMPLE_HTTP_DATA_TYPES_HPP

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