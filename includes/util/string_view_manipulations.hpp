/**
 * @file string_view_manipulations.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_STRING_VIEW_MANIPULATIONS_HPP
#define SIMPLE_HTTP_STRING_VIEW_MANIPULATIONS_HPP

#include <string>
#include <string_view>
#include <vector>

namespace simple {

using SubStrs = std::vector<std::string_view>;

inline auto split_first(std::string_view str, std::string_view delim) -> std::string_view {
  const size_t pos = str.find(delim);
  if (pos == std::string_view::npos) {
    return {};
  }

  return {str.begin(), pos};
}

}  // namespace simple

#endif