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