

#include <filesystem>

#include <pages/page_manager.hpp>
#include <util/file_operations.hpp>

namespace simpleHTTP {
std::optional<PageContent>
Pages::loadPage(std::string_view uri) {
  auto path = basePath / uri;
  auto fileContent = loadFile(path);

  if (!fileContent)
    return std::nullopt;

  return PageContent{ContentType::HTML, fileContent};
}
}  // namespace simpleHTTP