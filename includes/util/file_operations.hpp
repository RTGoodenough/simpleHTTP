#ifndef SIMPLE_HTTP_FILE_OPERATIONS_HPP
#define SIMPLE_HTTP_FILE_OPERATIONS_HPP

#include <filesystem>
#include <optional>
#include <string>

#include <types/data.types.hpp>

namespace simpleHTTP {
[[nodiscard]] File loadFile(const std::filesystem::path&);
}  // namespace simpleHTTP

#endif