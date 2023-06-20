#ifndef SIMPLE_HTTP_LOGGING_HPP
#define SIMPLE_HTTP_LOGGING_HPP

#include <iostream>

inline void debug(std::string_view message) {
#ifndef NDEBUG
  std::cout << message << '\n';
#endif
}

#endif