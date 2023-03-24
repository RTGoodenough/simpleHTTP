/**
 * @file file_operations.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_FILE_OPERATIONS_HPP
#define SIMPLE_HTTP_FILE_OPERATIONS_HPP

#include <filesystem>
#include <optional>
#include <string>

#include <types/data.types.hpp>

namespace simpleHTTP {
[[nodiscard]] File loadFile(const std::filesystem::path&);
}  // namespace simpleHTTP

#endif