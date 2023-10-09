/**
 * @file page_content.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_PAGE_CONTENT
#define SIMPLE_HTTP_PAGE_CONTENT

#include <filesystem>
#include <unordered_map>

#include <types/data.types.hpp>
#include <util/file_operations.hpp>

namespace simple {
auto to_content_str(Content) -> const std::string&;
auto to_content_type(const std::string&) -> Content;

struct PageContent {
  Content type;
  File    file;
};

struct PageContentView {
  Content     type{Content::INVALID};
  const char* data{nullptr};
  size_t      size{0};
};

enum class LoadResult {
  NOT_FOUND,
  INVALID,
  SUCCESS,
};

struct PageLoad {
  LoadResult      found{};
  PageContentView content;
};

inline auto file_type(const std::filesystem::path& path) -> Content {
  if (!path.has_extension()) {
    return Content::HTML;
  }

  auto ext = path.extension();
  return to_content_type(ext);
}
}  // namespace simple

#endif