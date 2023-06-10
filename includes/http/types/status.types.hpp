/**
 * @file status.types.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-24
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of simpleHTTP which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef SIMPLE_HTTP_TYPES_HPP
#define SIMPLE_HTTP_TYPES_HPP

#include <string>
#include <unordered_map>

namespace simple::http {
enum class Status {
  CONTINUE = 100,
  SWITCHING_PROTOCOLS = 101,
  OK = 200,
  CREATED = 201,
  ACCEPTED = 202,
  NON_AUTHORITATIVE_INFORMATION = 203,
  NO_CONTENT = 204,
  RESET_CONTENT = 205,
  PARTIAL_CONTENT = 206,
  IM_USED = 226,
  MULTIPLE_CHOICES = 300,
  MOVED_PERMANENTLY = 301,
  FOUND = 302,
  SEE_OTHER = 303,
  NOT_MODIFIED = 304,
  USE_PROXY = 305,
  TEMPORARY_REDIRECT = 307,
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  PAYMENT_REQUIRED = 402,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,
  NOT_ACCEPTABLE = 406,
  PROXY_AUTHENTICATION_REQUIRED = 407,
  REQUEST_TIMEOUT = 408,
  CONFLICT = 409,
  GONE = 410,
  LENGTH_REQUIRED = 411,
  PRECONDITION_FAILED = 412,
  REQUEST_ENTITY_TOO_LARGE = 413,
  REQUEST_URI_TOO_LONG = 414,
  UNSUPPORTED_MEDIA_TYPE = 415,
  REQUESTED_RANGE_NOT_SATISFIABLE = 416,
  EXPECTATION_FAILED = 417,
  IM_A_TEAPOT = 418,
  UPGRADE_REQUIRED = 426,
  PRECONDITION_REQUIRED = 428,
  TOO_MANY_REQUESTS = 429,
  REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
  UNAVAILABLE_FOR_LEGAL_REASONS = 451,
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
  BAD_GATEWAY = 502,
  SERVICE_UNAVAILABLE = 503,
  GATEWAY_TIMEOUT = 504,
  HTTP_VERSION_NOT_SUPPORTED = 505,
  NOT_EXTENDED = 510,
  NETWORK_AUTHENTICATION_REQUIRED = 511
};

inline const std::string& toStatusStr(Status status) {
  static const std::unordered_map<Status, const std::string> STATUS_STRS{
      {Status::CONTINUE, "Continue"},
      {Status::SWITCHING_PROTOCOLS, "Switching Protocols"},
      {Status::OK, "OK"},
      {Status::CREATED, "Created"},
      {Status::ACCEPTED, "Accepted"},
      {Status::NON_AUTHORITATIVE_INFORMATION, "Non-authoritative Information"},
      {Status::NO_CONTENT, "No Content"},
      {Status::RESET_CONTENT, "Reset Content"},
      {Status::PARTIAL_CONTENT, "Partial Content"},
      {Status::IM_USED, "Im Used"},
      {Status::MULTIPLE_CHOICES, "Multiple Choices"},
      {Status::MOVED_PERMANENTLY, "Moved Permanently"},
      {Status::FOUND, "Found"},
      {Status::SEE_OTHER, "See Other"},
      {Status::NOT_MODIFIED, "Not Modified"},
      {Status::USE_PROXY, "Use Proxy"},
      {Status::TEMPORARY_REDIRECT, "Temporary"},
      {Status::BAD_REQUEST, "Bad Request"},
      {Status::UNAUTHORIZED, "Unauthorized"},
      {Status::PAYMENT_REQUIRED, "Payment Required"},
      {Status::FORBIDDEN, "Forbidden"},
      {Status::NOT_FOUND, "Not Found"},
      {Status::METHOD_NOT_ALLOWED, "Method Not Allowed"},
      {Status::NOT_ACCEPTABLE, "Not Acceptable"},
      {Status::PROXY_AUTHENTICATION_REQUIRED, "Proxy Authentication Required"},
      {Status::REQUEST_TIMEOUT, "Request Timeout"},
      {Status::CONFLICT, "Conflict"},
      {Status::GONE, "Gone"},
      {Status::LENGTH_REQUIRED, "Length Required"},
      {Status::PRECONDITION_FAILED, "Precondition Failed"},
      {Status::REQUEST_ENTITY_TOO_LARGE, "Request Entity Too Large"},
      {Status::REQUEST_URI_TOO_LONG, "Request URI Too Long"},
      {Status::UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type"},
      {Status::REQUESTED_RANGE_NOT_SATISFIABLE, "Requested Range Not Satisfiable"},
      {Status::EXPECTATION_FAILED, "Expectation Failed"},
      {Status::IM_A_TEAPOT, "I'm A Teapot"},
      {Status::UPGRADE_REQUIRED, "Upgrade Required"},
      {Status::PRECONDITION_REQUIRED, "Precondition Required"},
      {Status::TOO_MANY_REQUESTS, "Too Many Requests"},
      {Status::REQUEST_HEADER_FIELDS_TOO_LARGE, "Request Header Fields Too Large"},
      {Status::UNAVAILABLE_FOR_LEGAL_REASONS, "Unavailable For Legal Reasons"},
      {Status::INTERNAL_SERVER_ERROR, "Internal Server Error"},
      {Status::NOT_IMPLEMENTED, "Not Implemented"},
      {Status::BAD_GATEWAY, "Bad Gateway"},
      {Status::SERVICE_UNAVAILABLE, "Service Unavailable"},
      {Status::GATEWAY_TIMEOUT, "Gateway Timeout"},
      {Status::HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported"},
      {Status::NOT_EXTENDED, "Not Extended"},
      {Status::NETWORK_AUTHENTICATION_REQUIRED, "Network Authentication Required"}};

  return STATUS_STRS.at(status);
}

inline const std::string& toStatusNumStr(Status status) {
  static const std::unordered_map<Status, const std::string> STATUS_NUMBER_STRS{
      {Status::CONTINUE, "100"},
      {Status::SWITCHING_PROTOCOLS, "101"},
      {Status::OK, "200"},
      {Status::CREATED, "201"},
      {Status::ACCEPTED, "202"},
      {Status::NON_AUTHORITATIVE_INFORMATION, "203"},
      {Status::NO_CONTENT, "204"},
      {Status::RESET_CONTENT, "205"},
      {Status::PARTIAL_CONTENT, "206"},
      {Status::IM_USED, "226"},
      {Status::MULTIPLE_CHOICES, "300"},
      {Status::MOVED_PERMANENTLY, "301"},
      {Status::FOUND, "302"},
      {Status::SEE_OTHER, "303"},
      {Status::NOT_MODIFIED, "304"},
      {Status::USE_PROXY, "305"},
      {Status::TEMPORARY_REDIRECT, "307"},
      {Status::BAD_REQUEST, "400"},
      {Status::UNAUTHORIZED, "401"},
      {Status::PAYMENT_REQUIRED, "402"},
      {Status::FORBIDDEN, "403"},
      {Status::NOT_FOUND, "404"},
      {Status::METHOD_NOT_ALLOWED, "405"},
      {Status::NOT_ACCEPTABLE, "406"},
      {Status::PROXY_AUTHENTICATION_REQUIRED, "407"},
      {Status::REQUEST_TIMEOUT, "408"},
      {Status::CONFLICT, "409"},
      {Status::GONE, "410"},
      {Status::LENGTH_REQUIRED, "411"},
      {Status::PRECONDITION_FAILED, "412"},
      {Status::REQUEST_ENTITY_TOO_LARGE, "413"},
      {Status::REQUEST_URI_TOO_LONG, "414"},
      {Status::UNSUPPORTED_MEDIA_TYPE, "415"},
      {Status::REQUESTED_RANGE_NOT_SATISFIABLE, "416"},
      {Status::EXPECTATION_FAILED, "417"},
      {Status::IM_A_TEAPOT, "418"},
      {Status::UPGRADE_REQUIRED, "426"},
      {Status::PRECONDITION_REQUIRED, "428"},
      {Status::TOO_MANY_REQUESTS, "429"},
      {Status::REQUEST_HEADER_FIELDS_TOO_LARGE, "431"},
      {Status::UNAVAILABLE_FOR_LEGAL_REASONS, "451"},
      {Status::INTERNAL_SERVER_ERROR, "500"},
      {Status::NOT_IMPLEMENTED, "501"},
      {Status::BAD_GATEWAY, "502"},
      {Status::SERVICE_UNAVAILABLE, "503"},
      {Status::GATEWAY_TIMEOUT, "504"},
      {Status::HTTP_VERSION_NOT_SUPPORTED, "505"},
      {Status::NOT_EXTENDED, "510"},
      {Status::NETWORK_AUTHENTICATION_REQUIRED, "511"}};

  return STATUS_NUMBER_STRS.at(status);
}

}  // namespace simple::http

#endif