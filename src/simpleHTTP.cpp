
#include <spdlog/spdlog.h>

#include <server/shttp_Server.hpp>

int
main() {
  spdlog::set_level(spdlog::level::debug);
  simpleHTTP::Server server;
  server.start();
}