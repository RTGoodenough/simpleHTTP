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

auto check_path(std::string_view uri) -> bool { return uri.find("..") == std::string_view::npos; }

namespace simple {
auto Pages::load_page(std::string_view uri) -> PageLoad {
  debug("Load Page");
  if (uri.empty() || (uri.size() == 1 && uri.at(0) == '/')) {
    return {LoadResult::SUCCESS, _cache.get_page(_basePath / "index.html")};
  }

  if (!check_path(uri)) {
    debug("Invalid Path" + std::string(uri));
    return {LoadResult::INVALID, _cache.get_page(_basePath / "NotFound.html")};
  }

  auto path = _basePath / uri.substr(1);
  auto page = _cache.get_page(path);

  if (page.data) {
    debug("Page Loaded");
    return {LoadResult::SUCCESS, page};
  }

  debug("Page Not Found");
  return {LoadResult::NOT_FOUND, _cache.get_page(_basePath / "NotFound.html")};
}

void Pages::set_path(std::string_view path) { _basePath = path; }

auto Pages::use_file(const std::filesystem::path& path) -> File {
  auto file = load_file(path);

  if (file) {
    return file.value();
  }

  return {};
}
}  // namespace simple