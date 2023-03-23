
#include <http/types/header.types.hpp>

namespace simpleHTTP {
const std::unordered_map<HeaderType, std::string> HeaderStrs{
    {A_IM, "A-IM"},
    {ACCEPT, "Accept"},
    {ACCEPT_CHARSET, "Accept-Charset"},
    {ACCEPT_ENCODING, "Accept-Encoding"},
    {ACCEPT_LANGUAGE, "Accept-Language"},
    {ACCEPT_DATETIME, "Accept-Datetime"},
    {ACCESS_CONTROL_REQUEST_METHOD, "Access-Control-Request-Method"},
    {ACCESS_CONTROL_REQUEST_HEADERS, "Access-Control-Request-Headers"},
    {AUTHORIZATION, "Authorization"},
    {CACHE_CONTROL, "Cache-Control"},
    {CONNECTION, "Connection"},
    {CONTENT_LENGTH, "Content-Length"},
    {CONTENT_TYPE, "Content-Type"},
    {COOKIE, "Cookie"},
    {DATE, "Date"},
    {EXPECT, "Expect"},
    {FORWARDED, "Forwarded"},
    {FROM, "From"},
    {HOST, "Host"},
    {IF_MATCH, "If-Match"},
    {IF_MODIFIED_SINCE, "If-Modified-Since"},
    {IF_NONE_MATCH, "If-None-Match"},
    {IF_RANGE, "If-Range"},
    {IF_UNMODIFIED_SINCE, "If-Unmodified-Since"},
    {MAX_FORWARDS, "Max-Forwards"},
    {ORIGIN, "Origin"},
    {PRAGMA, "Pragma"},
    {PROXY_AUTHORIZATION, "Proxy-Authorization"},
    {RANGE, "Range"},
    {REFERER, "Referer"},
    {TE, "TE"},
    {USER_AGENT, "User-Agent"},
    {UPGRADE, "Upgrade"},
    {VIA, "Via"},
    {WARNING, "Warning"},
    {ACCEPT_CH, "Accept-Ch"},
    {ACCESS_CONTROL_ALLOW_ORIGIN, "Access-Control-Allow-Origin"},
    {ACCESS_CONTROL_ALLOW_CREDENTIALS, "Access-Control-Allow-Credentials"},
    {ACCESS_CONTROL_EXPOSE_HEADERS, "Access-Control-Expose-Headers"},
    {ACCESS_CONTROL_MAX_AGE, "Access-Control-Max-Age"},
    {ACCESS_CONTROL_ALLOW_METHODS, "Access-Control-Allow-Methods"},
    {ACCESS_CONTROL_ALLOW_HEADERS, "Access-Control-Allow-Headers"},
    {ACCEPT_PATCH, "Accept-Patch"},
    {ACCEPT_RANGES, "Accept-Ranges"},
    {AGE, "Age"},
    {ALLOW, "Allow"},
    {ALT_SVC, "Alt-Svc"},
    {CONTENT_DISPOSITION, "Content-Disposition"},
    {CONTENT_ENCODING, "Content-Encoding"},
    {CONTENT_LANGUAGE, "Content-Language"},
    {CONTENT_LOCATION, "Content-Location"},
    {CONTENT_MD5, "Content-Md5"},
    {CONTENT_RANGE, "Content-Range"},
    {DELTA_BASE, "Delta-Base"},
    {ETAG, "Etag"},
    {EXPIRES, "Expires"},
    {IM, "Im"},
    {LAST, "Last"},
    {LINK, "Link"},
    {P3P, "P3p"},
    {PREFERENCE_APPLIED, "Preference-Applied"},
    {PROXY_AUTHENTICATE, "Proxy-Authenticate"},
    {PUBLIC_KEY_PINS, "Public-Key-Pins"},
    {RETRY_AFTER, "Retry-After"},
    {SERVER, "Server"},
    {SET_COOKIE, "Set-Cookie"},
    {STRICT_TRANSPORT_SECURITY, "Strict-Transport-Security"},
    {TRAILER, "Trailer"},
    {TRANSFER_ENCODING, "Transfer-Encoding"},
    {TK, "Tk"},
    {VARY, "Vary"},
    {WWW_AUTHENTICATE, "WWW-Authenticate"},
    {X_FRAME_OPTIONS, "X-Frame-Options"},
};
}