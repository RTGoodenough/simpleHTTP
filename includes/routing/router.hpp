#ifndef YASUMI_ROUTER_HPP
#define YASUMI_ROUTER_HPP

#include <unordered_map>
#include <unordered_set>

#include <spdlog/spdlog.h>

#include <routing/router.types.hpp>
#include <types/data.types.hpp>

namespace simpleHTTP {
class RouterException : public std::runtime_error {
 public:
  RouterException(const std::string& message) : std::runtime_error(message) {}
  static void Throw(const std::string& message) { throw RouterException(message); }
};

class Router {
 public:
  ~Router() = default;
  Router() = default;
  Router(const Router&);
  Router& operator=(const Router&);
  Router(Router&&);
  Router& operator=(Router&&);

  [[nodiscard]] ByteVector route(std::optional<HTTP::Request>&);

 private:
};
}  // namespace simpleHTTP

#endif