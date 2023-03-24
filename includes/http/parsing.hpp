/**
 * @file parsing.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <optional>
#include <string_view>

#include <http/types/status.types.hpp>
namespace simpleHTTP {
namespace Parsing {
[[nodiscard]] std::optional<std::string_view> getRoute(std::string_view);
}
}  // namespace simpleHTTP

#endif