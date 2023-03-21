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

 private:
  std::filesystem::path basePath;
};
}  // namespace simpleHTTP

#endif