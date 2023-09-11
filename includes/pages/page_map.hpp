/**
 * @file page_map.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_PAGE_MAP_HPP
#define SIMPLE_HTTP_PAGE_MAP_HPP

#include <filesystem>
#include <map>

#include <pages/page_content.hpp>
#include "types/data.types.hpp"

namespace simple {
class PageMap {
 public:
  void set(const std::filesystem::path& filePath, PageContent&& content) {
    _contentMap[filePath] = std::move(content);
  }

  [[nodiscard]] auto get(const std::filesystem::path& filePath) -> PageContentView {
    auto iter = _contentMap.find(filePath);
    if (iter == _contentMap.end()) {
      return {Content::NOT_FOUND, nullptr, 0};
    }

    return {iter->second.type, iter->second.file.data(), iter->second.file.size()};
  }

 private:
  std::map<std::string, PageContent> _contentMap;
};
}  // namespace simple

#endif