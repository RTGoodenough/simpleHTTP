/**
 * @file header.types.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTPP_HEADER_TYPES
#define SIMPLE_HTPP_HEADER_TYPES

#include <string>
#include <unordered_map>

namespace simpleHTTP {
enum class Header {
  A_IM,
  ACCEPT,
  ACCEPT_CHARSET,
  ACCEPT_ENCODING,
  ACCEPT_LANGUAGE,
  ACCEPT_DATETIME,
  ACCESS_CONTROL_REQUEST_METHOD,
  ACCESS_CONTROL_REQUEST_HEADERS,
  AUTHORIZATION,
  CACHE_CONTROL,
  CONNECTION,
  CONTENT_LENGTH,
  CONTENT_TYPE,
  COOKIE,
  DATE,
  EXPECT,
  FORWARDED,
  FROM,
  HOST,
  IF_MATCH,
  IF_MODIFIED_SINCE,
  IF_NONE_MATCH,
  IF_RANGE,
  IF_UNMODIFIED_SINCE,
  MAX_FORWARDS,
  ORIGIN,
  PRAGMA,
  PROXY_AUTHORIZATION,
  RANGE,
  REFERER,
  TE,
  USER_AGENT,
  UPGRADE,
  VIA,
  WARNING,
  ACCEPT_CH,
  ACCESS_CONTROL_ALLOW_ORIGIN,
  ACCESS_CONTROL_ALLOW_CREDENTIALS,
  ACCESS_CONTROL_EXPOSE_HEADERS,
  ACCESS_CONTROL_MAX_AGE,
  ACCESS_CONTROL_ALLOW_METHODS,
  ACCESS_CONTROL_ALLOW_HEADERS,
  ACCEPT_PATCH,
  ACCEPT_RANGES,
  AGE,
  ALLOW,
  ALT_SVC,
  CONTENT_DISPOSITION,
  CONTENT_ENCODING,
  CONTENT_LANGUAGE,
  CONTENT_LOCATION,
  CONTENT_MD5,
  CONTENT_RANGE,
  DELTA_BASE,
  ETAG,
  EXPIRES,
  IM,
  LAST,
  LINK,
  P3P,
  PREFERENCE_APPLIED,
  PROXY_AUTHENTICATE,
  PUBLIC_KEY_PINS,
  RETRY_AFTER,
  SERVER,
  SET_COOKIE,
  STRICT_TRANSPORT_SECURITY,
  TRAILER,
  TRANSFER_ENCODING,
  TK,
  VARY,
  WWW_AUTHENTICATE,
  X_FRAME_OPTIONS,
};

extern const std::unordered_map<Header, std::string> HeaderStrs;

}  // namespace simpleHTTP

#endif
