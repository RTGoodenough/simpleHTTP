/**
 * @file config.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-06-10
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_CONFIG_HPP
#define SIMPLE_CONFIG_HPP

#include <filesystem>

#include "pages/page_manager_config.hpp"
#include "server/server_config.hpp"

namespace simple {
struct Config {
  explicit Config(const std::filesystem::path& filepath) { loadFile(filepath); }

  ServerConfig      serverConf;
  PageManagerConfig pageManagerConf;

  Config() = default;
  ~Config() = default;
  Config(const Config&) = default;
  Config(Config&&) noexcept = default;
  auto operator=(const Config&) -> Config& = default;
  auto operator=(Config&&) noexcept -> Config& = default;

 private:
  static void loadFile(const std::filesystem::path& filepath) {
    if (std::filesystem::is_regular_file(filepath)) {
      // TODO(rolland): load the file
    }
  }
};
}  // namespace simple

#endif