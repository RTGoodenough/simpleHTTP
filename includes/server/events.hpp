#ifndef SIMPLE_HTTP_MESSAGE_EVENT_HPP
#define SIMPLE_HTTP_MESSAGE_EVENT_HPP

#include <cstddef>

namespace simple::event {
struct Connection {
  int sock_fd;
};

struct Message {
  int         sock_fd;
  const char* message;
  size_t      readCnt;
};
}  // namespace simple::event

#endif