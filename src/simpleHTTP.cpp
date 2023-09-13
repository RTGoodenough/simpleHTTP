/**
 * @file simple.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <pirate.hpp>

#include <server/shttp_Server.hpp>

auto main(int argc, const char** argv) -> int {
  simple::Server::setup_args();
  pirate::Args   args{argc, argv};
  simple::Server server(args);
  server.start();
}