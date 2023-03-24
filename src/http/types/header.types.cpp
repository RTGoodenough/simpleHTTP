
#include <http/types/header.types.hpp>

namespace simpleHTTP {
const std::unordered_map<Header, std::string> HeaderStrs{
    {Header::A_IM, "A-IM"},
    {Header::ACCEPT, "Accept"},
    {Header::ACCEPT_CHARSET, "Accept-Charset"},
    {Header::ACCEPT_ENCODING, "Accept-Encoding"},
    {Header::ACCEPT_LANGUAGE, "Accept-Language"},
    {Header::ACCEPT_DATETIME, "Accept-Datetime"},
    {Header::ACCESS_CONTROL_REQUEST_METHOD, "Access-Control-Request-Method"},
    {Header::ACCESS_CONTROL_REQUEST_HEADERS, "Access-Control-Request-Headers"},
    {Header::AUTHORIZATION, "Authorization"},
    {Header::CACHE_CONTROL, "Cache-Control"},
    {Header::CONNECTION, "Connection"},
    {Header::CONTENT_LENGTH, "Content-Length"},
    {Header::CONTENT_TYPE, "Content-Type"},
    {Header::COOKIE, "Cookie"},
    {Header::DATE, "Date"},
    {Header::EXPECT, "Expect"},
    {Header::FORWARDED, "Forwarded"},
    {Header::FROM, "From"},
    {Header::HOST, "Host"},
    {Header::IF_MATCH, "If-Match"},
    {Header::IF_MODIFIED_SINCE, "If-Modified-Since"},
    {Header::IF_NONE_MATCH, "If-None-Match"},
    {Header::IF_RANGE, "If-Range"},
    {Header::IF_UNMODIFIED_SINCE, "If-Unmodified-Since"},
    {Header::MAX_FORWARDS, "Max-Forwards"},
    {Header::ORIGIN, "Origin"},
    {Header::PRAGMA, "Pragma"},
    {Header::PROXY_AUTHORIZATION, "Proxy-Authorization"},
    {Header::RANGE, "Range"},
    {Header::REFERER, "Referer"},
    {Header::TE, "TE"},
    {Header::USER_AGENT, "User-Agent"},
    {Header::UPGRADE, "Upgrade"},
    {Header::VIA, "Via"},
    {Header::WARNING, "Warning"},
    {Header::ACCEPT_CH, "Accept-Ch"},
    {Header::ACCESS_CONTROL_ALLOW_ORIGIN, "Access-Control-Allow-Origin"},
    {Header::ACCESS_CONTROL_ALLOW_CREDENTIALS, "Access-Control-Allow-Credentials"},
    {Header::ACCESS_CONTROL_EXPOSE_HEADERS, "Access-Control-Expose-Headers"},
    {Header::ACCESS_CONTROL_MAX_AGE, "Access-Control-Max-Age"},
    {Header::ACCESS_CONTROL_ALLOW_METHODS, "Access-Control-Allow-Methods"},
    {Header::ACCESS_CONTROL_ALLOW_HEADERS, "Access-Control-Allow-Headers"},
    {Header::ACCEPT_PATCH, "Accept-Patch"},
    {Header::ACCEPT_RANGES, "Accept-Ranges"},
    {Header::AGE, "Age"},
    {Header::ALLOW, "Allow"},
    {Header::ALT_SVC, "Alt-Svc"},
    {Header::CONTENT_DISPOSITION, "Content-Disposition"},
    {Header::CONTENT_ENCODING, "Content-Encoding"},
    {Header::CONTENT_LANGUAGE, "Content-Language"},
    {Header::CONTENT_LOCATION, "Content-Location"},
    {Header::CONTENT_MD5, "Content-Md5"},
    {Header::CONTENT_RANGE, "Content-Range"},
    {Header::DELTA_BASE, "Delta-Base"},
    {Header::ETAG, "Etag"},
    {Header::EXPIRES, "Expires"},
    {Header::IM, "Im"},
    {Header::LAST, "Last"},
    {Header::LINK, "Link"},
    {Header::P3P, "P3p"},
    {Header::PREFERENCE_APPLIED, "Preference-Applied"},
    {Header::PROXY_AUTHENTICATE, "Proxy-Authenticate"},
    {Header::PUBLIC_KEY_PINS, "Public-Key-Pins"},
    {Header::RETRY_AFTER, "Retry-After"},
    {Header::SERVER, "Server"},
    {Header::SET_COOKIE, "Set-Cookie"},
    {Header::STRICT_TRANSPORT_SECURITY, "Strict-Transport-Security"},
    {Header::TRAILER, "Trailer"},
    {Header::TRANSFER_ENCODING, "Transfer-Encoding"},
    {Header::TK, "Tk"},
    {Header::VARY, "Vary"},
    {Header::WWW_AUTHENTICATE, "WWW-Authenticate"},
    {Header::X_FRAME_OPTIONS, "X-Frame-Options"},
};
}