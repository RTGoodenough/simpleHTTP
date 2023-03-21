
#include <fstream>

#include <util/file_operations.hpp>

namespace simpleHTTP {

const char*
loadFile(std::filesystem::path filepath) {

  if (!std::filesystem::exists(filepath))
    return nullptr;

  std::ifstream file(filepath);
  file.seekg(0, std::ios_base::end);
  size_t size = file.tellg();

  char* data = reinterpret_cast<char*>(malloc(size));

  file.seekg(0, std::ios_base::beg);
  file.read(data, size);

  file.close();
  return data;
}
}  // namespace simpleHTTP