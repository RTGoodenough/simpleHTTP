#ifndef SIMPLE_HTTP_PAGE_CONTENT
#define SIMPLE_HTTP_PAGE_CONTENT

#include <filesystem>
#include <unordered_map>

#include <util/file_operations.hpp>

namespace simpleHTTP {

extern const std::unordered_map<Content, std::string> ContentStrs;
extern const std::unordered_map<std::string, Content> ExtTypeMap;

struct PageContent {
  Content type;
  File    file;
};

struct PageLoad {
  bool        found;
  PageContent content;
};
}  // namespace simpleHTTP

#endif