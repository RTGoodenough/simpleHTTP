
#include <fstream>

#include <spdlog/spdlog.h>

#include <util/file_operations.hpp>

namespace simpleHTTP {

ContentType
getFileType(const std::filesystem::path&) {
  return HTML;
}

File
loadFile(const std::filesystem::path& filepath) {
  auto type = getFileType(filepath);

  if (!std::filesystem::exists(filepath)) {
    spdlog::debug("File Doesn't Exist: {}", filepath.c_str());
    return {nullptr, 0};
  }

  std::ifstream file(filepath);
  file.seekg(0, std::ios_base::end);
  size_t size = file.tellg();

  char* data = reinterpret_cast<char*>(malloc(size + 1));

  file.seekg(0, std::ios_base::beg);
  file.read(data, size);
  data[size] = '\0';

  file.close();
  return {data, size};
}
}  // namespace simpleHTTP