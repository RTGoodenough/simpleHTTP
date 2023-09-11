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

#include <pages/page_cache.hpp>
#include <pages/page_content.hpp>

namespace simple {
class Pages {
 public:
  [[nodiscard]] auto loadPage(std::string_view) -> PageLoad;

 private:
  PageCache             _cache;
  std::filesystem::path _basePath = std::filesystem::current_path() / "temp/routes";

  [[nodiscard]] auto        useFile(std::string_view) -> PageContent;
  [[nodiscard]] static auto getContentType(const std::filesystem::path&) -> Content;

  [[nodiscard]] static auto useFile(const std::filesystem::path&) -> File;
};
}  // namespace simple

#endif