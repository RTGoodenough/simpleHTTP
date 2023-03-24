

#include <filesystem>

#include <pages/page_manager.hpp>

bool
checkPath(std::string_view uri) {
  if (uri.find("..") != std::string_view::npos) {
    return false;
  }
  return true;
}

namespace simpleHTTP {
PageLoad
Pages::loadPage(std::string_view uri) {

  if (uri == "/")
    return {true, PageContent{Content::HTML, useFile(basePath / "index.html")}};

  if (!checkPath(uri))
    return {false, PageContent{Content::HTML, useFile(basePath / "NotFound.html")}};

  auto path = basePath / uri.substr(1);

  if (!std::filesystem::exists(path) || std::filesystem::is_directory(path))
    return {false, PageContent{Content::HTML, useFile(basePath / "NotFound.html")}};

  auto type = fileType(path);
  if (type == Content::INVALID)
    return {false, PageContent{Content::HTML, useFile(basePath / "NotFound.html")}};

  auto file = useFile(path);
  if (file.content == nullptr)
    return {false, PageContent{Content::HTML, useFile(basePath / "NotFound.html")}};

  return {true, PageContent{type, file}};
}

void
Pages::contentUsed(File content) {
  if (content.content != nullptr)
    delete[] content.content;
}

Content
Pages::fileType(const std::filesystem::path& path) const {
  if (!path.has_extension()) {
    return Content::HTML;
  }

  auto ext = path.extension();
  if (ExtTypeMap.find(ext) == ExtTypeMap.end())
    return Content::INVALID;

  return ExtTypeMap.at(ext);
}

File
Pages::useFile(const std::filesystem::path& path) {
  auto file = loadFile(path);
  return file;
}

}  // namespace simpleHTTP