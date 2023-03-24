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

#include <pages/page_content.hpp>

namespace simpleHTTP {
class Pages {
 public:
  [[nodiscard]] PageLoad loadPage(std::string_view);

  void contentUsed(File);

 private:
  [[nodiscard]] PageContent useFile(std::string_view);
  [[nodiscard]] Content     getContentType(const std::filesystem::path&) const;

  [[nodiscard]] File useFile(const std::filesystem::path&);

  [[nodiscard]] Content fileType(const std::filesystem::path&) const;

  std::filesystem::path basePath = std::filesystem::current_path() / "routes";
};
}  // namespace simpleHTTP

#endif