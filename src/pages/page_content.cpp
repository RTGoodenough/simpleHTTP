
#include <pages/page_content.hpp>

namespace simpleHTTP {
const std::unordered_map<Content, std::string> ContentStrs = {
    {Content::HTML, "text/html"},
    {Content::JAVASCRIPT, "application/javascript"},
};

const std::unordered_map<std::string, Content> ExtTypeMap{{".html", Content::HTML}, {".js", Content::JAVASCRIPT}};
}  // namespace simpleHTTP