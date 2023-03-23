#ifndef SIMPLE_HTTP_PAGE_CONTENT
#define SIMPLE_HTTP_PAGE_CONTENT

#include <unordered_map>

#include <util/file_operations.hpp>

namespace simpleHTTP {

extern const std::unordered_map<ContentType, std::string> ContentTypeStrs;

struct PageContent {
  ContentType type;
  File        file;
};
}  // namespace simpleHTTP

#endif