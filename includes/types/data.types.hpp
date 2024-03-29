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

namespace simple {
using ByteVector = std::vector<char>;

enum class Content {
  INVALID,
  NOT_FOUND,
  BAD_REQUEST,
  HTML,
  JAVASCRIPT,
};

using File = std::vector<char>;
}  // namespace simple

#endif