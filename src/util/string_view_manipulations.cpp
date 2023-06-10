/**
 * @file string_view_manipulations.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <util/string_view_manipulations.hpp>

std::string_view simple::splitFirst(std::string_view str, std::string_view delim) {
  const size_t pos = str.find(delim);
  if (pos == std::string_view::npos) {
    return {};
  }

  return {str.begin(), pos};
}