/**
 * @file page_manager.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_PAGE_MANAGER
#define SIMPLE_HTTP_PAGE_MANAGER

#include <filesystem>
#include <string_view>

#include "pages/page_cache.hpp"
#include "pages/page_content.hpp"

namespace simple {
class Pages {
 public:
  [[nodiscard]] auto load_page(std::string_view) -> PageLoad;

  void set_path(std::string_view);

 private:
  PageCache             _cache;
  std::filesystem::path _basePath = std::filesystem::current_path();

  [[nodiscard]] auto        use_file(std::string_view) -> PageContent;
  [[nodiscard]] static auto get_content_type(const std::filesystem::path&) -> Content;

  [[nodiscard]] static auto use_file(const std::filesystem::path&) -> File;
};
}  // namespace simple

#endif