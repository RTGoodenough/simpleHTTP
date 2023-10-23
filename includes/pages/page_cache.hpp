/**
 * @file page_cache.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_PAGE_CACHE_HPP
#define SIMPLE_HTTP_PAGE_CACHE_HPP

#include <filesystem>
#include <mutex>

#include "pages/page_content.hpp"
#include "pages/page_map.hpp"
#include "types/data.types.hpp"
#include "util/file_operations.hpp"

namespace simple {
class PageCache {
 public:
  void clear() {
    std::lock_guard<std::mutex> lock{_mux};
    _map.clear();
  }

  auto get_page(const std::filesystem::path& filePath) -> PageContentView {
    std::lock_guard<std::mutex> lock{_mux};
    auto                        page = _map.get(filePath);
    if (page.data) {
      return page;
    }

    Content type = file_type(filePath);
    if (type == Content::NOT_FOUND || type == Content::INVALID) {
      return {type, nullptr, 0};
    }

    auto file = load_file(filePath);

    if (file) {
      _map.set(filePath,
               PageContent{type, std::move(file.value()), std::filesystem::last_write_time(filePath)});
    }

    return _map.get(filePath);
  }

 private:
  PageMap    _map;
  std::mutex _mux;
};
}  // namespace simple

#endif