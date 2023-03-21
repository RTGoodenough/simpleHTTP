#ifndef SIMPLE_HTTP_PAGE_CONTENT
#define SIMPLE_HTTP_PAGE_CONTENT

namespace simpleHTTP {

enum ContentType {
  HTML,
};

struct PageContent {
  ContentType type;
  const char* content;
};
}  // namespace simpleHTTP

#endif