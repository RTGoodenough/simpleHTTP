#ifndef SIMPLE_HTTP_PAGE_MANAGER
#define SIMPLE_HTTP_PAGE_MANAGER

#include <filesystem>
#include <string_view>

#include <pages/page_content.hpp>

namespace simpleHTTP {
class Pages {
 public:
  [[nodiscard]] PageLoad loadPage(std::string_view);

  void contentUsed(File);

 private:
  [[nodiscard]] PageContent useFile(std::string_view);
  [[nodiscard]] Content     getContentType(const std::filesystem::path&) const;

  [[nodiscard]] File useFile(const std::filesystem::path&);

  [[nodiscard]] Content fileType(const std::filesystem::path&) const;

  std::filesystem::path basePath = std::filesystem::current_path() / "routes";
};
}  // namespace simpleHTTP

#endif