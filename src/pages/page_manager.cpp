

#include <filesystem>

#include <spdlog/spdlog.h>

#include <pages/page_manager.hpp>
#include <util/file_operations.hpp>

bool
checkPath(std::string_view uri) {
  if (uri.find("..") != std::string_view::npos) {
    return false;
  }
  return true;
}

namespace simpleHTTP {
std::optional<PageContent>
Pages::loadPage(std::string_view uri) {

  if (!checkPath(uri))
    return std::nullopt;

  std::filesystem::path path = std::filesystem::current_path() / "routes";
  path /= uri.substr(1);
  spdlog::debug("Path: {}", path.c_str());
  auto fileContent = loadFile(path);

  if (!fileContent.content)
    return std::nullopt;

  return PageContent{ContentType::HTML, fileContent};
}

void
Pages::contentUsed(const char* content) {
  if (content != nullptr)
    delete[] content;
}

}  // namespace simpleHTTP