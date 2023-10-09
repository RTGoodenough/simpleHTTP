/**
 * @file logging.hpp
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

#ifndef SIMPLE_HTTP_LOGGING_HPP
#define SIMPLE_HTTP_LOGGING_HPP

#include <iostream>
#include <string_view>

#ifndef NDEBUG
inline void debug(std::string_view message) { std::cout << "[Debug] " << message << '\n'; }
#else
inline void debug(std::string_view /*message*/) {}
#endif

inline void warn(std::string_view message) { std::cout << "[Warn] " << message << '\n'; }

inline void error(std::string_view message) { std::cout << "[ERROR] " << message << '\n'; }

inline void info(std::string_view message) { std::cout << "[Info] " << message << '\n'; }

#endif