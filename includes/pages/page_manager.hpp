#ifndef SIMPLE_HTTP_PAGE_MANAGER
#define SIMPLE_HTTP_PAGE_MANAGER

#include <filesystem>
#include <optional>
#include <string_view>

#include <pages/page_content.hpp>

namespace simpleHTTP {
class Pages {
 public:
  [[nodiscard]] std::optional<PageContent> loadPage(std::string_view);

  void contentUsed(const char*);
};
}  // namespace simpleHTTP

#endif