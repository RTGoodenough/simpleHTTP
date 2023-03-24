/**
 * @file simpleHTTP.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <spdlog/spdlog.h>

#include <server/shttp_Server.hpp>

int
main() {
  spdlog::set_level(spdlog::level::debug);
  simpleHTTP::Server server;
  server.start();
}