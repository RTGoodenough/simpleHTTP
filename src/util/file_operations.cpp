
#include <fstream>

#include <util/file_operations.hpp>

namespace simpleHTTP {

File
loadFile(const std::filesystem::path& filepath) {
  if (!std::filesystem::exists(filepath) || std::filesystem::is_directory(filepath)) {
    return {nullptr, 0};
  }

  std::ifstream file(filepath);
  file.seekg(0, std::ios_base::end);
  size_t size = static_cast<size_t>(file.tellg());

  char* data = reinterpret_cast<char*>(malloc(size + 1));

  file.seekg(0, std::ios_base::beg);
  file.read(data, static_cast<std::streamsize>(size));
  data[size] = '\0';

  file.close();
  return {data, size};
}
}  // namespace simpleHTTP