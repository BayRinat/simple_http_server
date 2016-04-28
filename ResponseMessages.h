/*++

Abstract:
  Response messages

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_RESPONSEMESSAGES_H
#define HTTP_SERVER_RESPONSEMESSAGES_H

#include <string>

namespace http {
namespace server {
namespace message {

static const std::string OK = "HTTP/1.1 200 OK\r\n\r\n";;
static const std::string BAD_REQUEST = "HTTP/1.1 400 Bad Request\r\n\r\n";;
static const std::string NOT_FOUND = "HTTP/1.1 404 Not Found\r\n\r\n";
static const std::string INTERNAL_SERVER_ERROR = "HTTP/1.1 500 Internal Server Error\r\n\r\n";

} // namespace message
} // namespace server
} // namespace http

#endif // HTTP_SERVER_RESPONSEMESSAGES_H
