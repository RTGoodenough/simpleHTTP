

#include <http/respond.hpp>

namespace simpleHTTP {
namespace Respond {
ByteVector
WebPage(const PageContent&, Socket&) {}

ByteVector
NotFound(const HTTP::Request&, Socket&) {}

}  // namespace Respond
}  // namespace simpleHTTP
