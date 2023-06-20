#ifndef SIMPLE_HTTP_TOKEN_HPP
#define SIMPLE_HTTP_TOKEN_HPP

#include <string_view>

enum class TokenType {
  END,
  ID,
  NUMBER,
  LINE_END,
  CHAR,
  STATUS,
  HEADER,
  METHOD,
  VERSION,
  SCHEME,
  // Status
  CONTINUE,
  SWITCHING_PROTOCOLS,
  OK,
  CREATED,
  ACCEPTED,
  NON_AUTHORITATIVE_INFORMATION,
  NO_CONTENT,
  RESET_CONTENT,
  PARTIAL_CONTENT,
  MULTIPLE_CHOICES,
  MOVED_PERMANENTLY,
  FOUND,
  SEE_OTHER,
  NOT_MODIFIED,
  USE_PROXY,
  TEMPORARY_REDIRECT,
  BAD_REQUEST,
  UNAUTHORIZED,
  PAYMENT_REQUIRED,
  FORBIDDEN,
  NOT_FOUND,
  METHOD_NOT_ALLOWED,
  NOT_ACCEPTABLE,
  PROXY_AUTHENTICATION_REQUIRED,
  REQUEST_TIME_OUT,
  CONFLICT,
  GONE,
  LENGTH_REQUIRED,
  PRECONDITION_FAILED,
  REQUEST_ENTITY_TOO_LARGE,
  REQUEST_URI_TOO_LARGE,
  UNSUPPORTED_MEDIA_TYPE,
  REQUESTED_RANGE_NOT_SATISFIABLE,
  EXPECTATION_FAILED,
  INTERNAL_SERVER_ERROR,
  NOT_IMPLEMENTED,
  BAD_GATEWAY,
  SERVICE_UNAVAILABLE,
  GATEWAY_TIME_OUT,
  HTTP_VERSION_NOT_SUPPORTED,
  // Methods
  OPTIONS,
  GET,
  HEAD,
  POST,
  PUT,
  DELETE,
  TRACE,
  CONNECT,
  // common characters
  COMMA,
  PERIOD,
  EXLAIM,
  DQUOTE,
  POUND,
  DOLLAR,
  PERCENT,
  AMPER,
  SQUOTE,
  BTICK,
  LPAREN,
  RPAREN,
  ASTERISK,
  PLUS,
  MINUS,
  FSLASH,
  SEMICOLON,
  COLON,
  GT,
  LT,
  EQ,
  QUESTION,
  AT,
  LBRACKET,
  RBRACKET,
  BSLASH,
  CARROT,
  UNDER,
  PIPE,
  TILDE,
  RETURN,
};

/*

Continue
Switching Protocols
OK
Created
Accepted
Non-Authoritative Information
No Content
Reset Content
Partial Content
Multiple Choices
Moved Permanently
Found
See Other
Not Modified
Use Proxy
Temporary Redirect
Bad Request
Unauthorized
Payment Required
Forbidden
Not Found
Method Not Allowed
Not Acceptable
Proxy Authentication Required
Request Time-out
Conflict
Gone
Length Required
Precondition Failed
Request Entity Too Large
Request-URI Too Large
Unsupported Media Type
Requested range not satisfiable
Expectation Failed
Internal Server Error
Not Implemented
Bad Gateway
Service Unavailable
Gateway Time-out
HTTP Version not supported
*/

struct Token {
  TokenType        type;
  std::string_view value;

  [[nodiscard]] inline bool isType(TokenType tType) const { return type == tType; }
};

#endif