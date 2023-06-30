

#include <gtest/gtest.h>

#include <http/parsing.hpp>
#include "http/types/header.types.hpp"
#include "http/types/http.types.hpp"

TEST(Parsing, ParseRequest) {
  simple::http::Parser sut;
  std::string          req =
      "GET /hello.html HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; "
      "Windows "
      "NT)\r\nHost: www.tutorialspoint.com\r\nAccept-Language: en-us\r\nAccept-Encoding: "
      "gzip, deflate\r\nConnection: Keep-Alive\r\n\r\ntest";

  auto parsed = sut.parse(req);

  EXPECT_TRUE(parsed);
  if (parsed) {
    EXPECT_EQ(parsed->getContent(), "test");
    EXPECT_EQ(parsed->getMethod(), simple::http::Method::GET);
    EXPECT_EQ(parsed->getUri().host, "www.tutorialspoint.com");
    EXPECT_EQ(parsed->getUri().uri, "/hello.html");
    EXPECT_EQ(parsed->getHeader(simple::http::Header::ACCEPT_LANGUAGE), "en-us");
    EXPECT_EQ(parsed->getHeader(simple::http::Header::ACCEPT_ENCODING), "gzip, deflate");
    EXPECT_EQ(parsed->getHeader(simple::http::Header::CONNECTION), "Keep-Alive");
  }

  std::string req2 =
      "POST /cgi-bin/process.cgi HTTP/1.1\r\n"
      "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
      "Host: www.tutorialspoint.com\r\n"
      "Content-Type: text/xml; charset=utf-8\r\n"
      "Content-Length: 98\r\n"
      "Accept-Language: en-us\r\n"
      "Accept-Encoding: gzip, deflate\r\n"
      "Connection: Keep-Alive\r\n\r\n"
      "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
      "<string xmlns=\"http://clearforest.com/\">string</string>";

  auto parsed2 = sut.parse(req2);

  if (parsed2) {
    EXPECT_EQ(parsed2->getContent(),
              "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n<string "
              "xmlns=\"http://clearforest.com/\">string</string>");
    EXPECT_EQ(parsed2->getMethod(), simple::http::Method::POST);
    EXPECT_EQ(parsed2->getUri().host, "www.tutorialspoint.com");
    EXPECT_EQ(parsed2->getUri().uri, "/cgi-bin/process.cgi");
    EXPECT_EQ(parsed2->getHeader(simple::http::Header::ACCEPT_LANGUAGE), "en-us");
    EXPECT_EQ(parsed2->getHeader(simple::http::Header::ACCEPT_ENCODING), "gzip, deflate");
    EXPECT_EQ(parsed2->getHeader(simple::http::Header::CONNECTION), "Keep-Alive");
    EXPECT_EQ(parsed2->getHeader(simple::http::Header::CONTENT_TYPE),
              "text/xml; charset=utf-8");
    EXPECT_EQ(parsed2->getHeader(simple::http::Header::CONTENT_LENGTH), "98");
  }

  EXPECT_TRUE(parsed2);
}

TEST(Parsing, ParseRequestImproper) {
  simple::http::Parser sut;
  std::string          req =
      "GET /hello.html HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; "
      "Windows "
      "NT)\r\nHost: www.tutorialspoint.com\r\nAccept-Language: en-us\r\nAccept-Encoding: "
      "gzip, deflate\r\nConnection: Keep-Alive\r\n\r\ntest";

  auto parsed = sut.parse(req);
}