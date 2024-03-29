/**
 * @file respond.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef HTTP_BUILDER_HPP
#define HTTP_BUILDER_HPP

#include <string_view>

#include <http/types/status.types.hpp>
#include <pages/page_content.hpp>
#include <socket/socket.types.hpp>
#include <types/data.types.hpp>

namespace simple::respond {
void web_page(http::Status, PageContentView, sock_fd);
void not_found(sock_fd);
void bad_request(sock_fd);
}  // namespace simple::respond

#endif