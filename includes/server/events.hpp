/**
 * @file events.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_MESSAGE_EVENT_HPP
#define SIMPLE_HTTP_MESSAGE_EVENT_HPP

#include <cstddef>
#include <vector>

namespace simple::event {
struct Connection {
  int sock_fd;
};

struct Message {
  int               sock_fd;
  std::vector<char> message;
  size_t            readCnt;
};
}  // namespace simple::event

#endif