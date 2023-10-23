#ifndef SIMPLE_HTTP_CLASS_TYPES_HPP
#define SIMPLE_HTTP_CLASS_TYPES_HPP

#define DEFAULT_CONSTRUCIBLE(T) \
 public:                        \
  T() = default;

#define DEFAULT_DESTRUCIBLE(T) \
 public:                       \
  ~T() = default;

#define DEFAULT_COPYABLE(T) \
 public:                    \
  T(const T&) = default;    \
  auto operator=(const T&)->T& = default;

#define DEFAULT_MOVEABLE(T) \
 public:                    \
  T(T&&) = default;         \
  auto operator=(T&&)->T& = default;

#define DEFAULT_COPY_MOVE(T) \
 public:                     \
  DEFAULT_COPYABLE(T)        \
  DEFAULT_MOVEABLE(T)

#define NON_DEFAULT_CONSTRUCIBLE(T) \
 public:                            \
  T() = delete;

#define NON_COPYABLE(T) \
 public:                \
  T(const T&) = delete; \
  auto operator=(const T&)->T& = delete;

#define NON_MOVEABLE(T) \
 public:                \
  T(T&&) = delete;      \
  auto operator=(T&&)->T& = delete;

#endif