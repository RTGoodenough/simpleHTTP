/**
 * @file page_content.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <pages/page_content.hpp>

namespace simpleHTTP {
const std::unordered_map<Content, std::string> ContentStrs = {
    {Content::HTML, "text/html"},
    {Content::JAVASCRIPT, "application/javascript"},
};

const std::unordered_map<std::string, Content> ExtTypeMap{{".html", Content::HTML}, {".js", Content::JAVASCRIPT}};
}  // namespace simpleHTTP