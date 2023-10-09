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
#include "types/data.types.hpp"

namespace simple {
auto to_content_str(Content contentType) -> const std::string& {
  static const std::unordered_map<Content, std::string> CONTENT_STRS = {
      {Content::HTML, "text/html"},
      {Content::JAVASCRIPT, "application/javascript"},
  };

  return CONTENT_STRS.at(contentType);
}
auto to_content_type(const std::string& fileExt) -> Content {
  static const std::unordered_map<std::string, Content> EXT_TYPE_MAP{{".html", Content::HTML},
                                                                     {".js", Content::JAVASCRIPT}};

  if (EXT_TYPE_MAP.find(fileExt) == EXT_TYPE_MAP.end()) {
    return Content::INVALID;
  }

  return EXT_TYPE_MAP.at(fileExt);
}

}  // namespace simple