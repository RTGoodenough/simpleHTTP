/**
 * @file page_manager.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 *
 * @copyright Copyright 2023 Rolland Goodenough
 *
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <filesystem>

#include <logging/logging.hpp>

#include <pages/page_content.hpp>
#include <pages/page_manager.hpp>

bool checkPath(std::string_view uri) { return uri.find("..") == std::string_view::npos; }

namespace simple {
PageLoad Pages::loadPage(std::string_view uri) {
  if (uri.empty() || (uri.size() == 1 && uri.at(0) == '/')) {
    return {LoadResult::SUCCESS, _cache.getPage(_basePath / "index.html")};
  }

  if (!checkPath(uri)) {
    return {LoadResult::INVALID, _cache.getPage(_basePath / "NotFound.html")};
  }

  auto path = _basePath / uri.substr(1);
  auto page = _cache.getPage(path);

  if (page.data) {
    debug("Page Loaded");
    return {LoadResult::SUCCESS, page};
  }

  debug("Page Not Found");
  return {LoadResult::NOT_FOUND, _cache.getPage(_basePath / "NotFound.html")};
}

File Pages::useFile(const std::filesystem::path& path) {
  auto file = loadFile(path);

  if (file) {
    return file.value();
  }

  return {};
}
}  // namespace simple