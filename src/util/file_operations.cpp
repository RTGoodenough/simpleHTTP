/**
 * @file file_operations.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <fstream>

#include <util/file_operations.hpp>

namespace simple {

auto loadFile(const std::filesystem::path& filepath) -> std::optional<File> {
  if (!std::filesystem::exists(filepath) || std::filesystem::is_directory(filepath)) {
    return std::nullopt;
  }

  std::ifstream file(filepath);
  file.seekg(0, std::ios_base::end);
  size_t size = static_cast<size_t>(file.tellg());

  auto data = File(size);

  file.seekg(0, std::ios_base::beg);
  file.read(data.data(), static_cast<std::streamsize>(size));

  file.close();
  return {data};
}
}  // namespace simple