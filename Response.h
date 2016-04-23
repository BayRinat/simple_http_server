/*++

Abstract:
  Response class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_RESPONSE_H
#define HTTP_SERVER_RESPONSE_H

#include <boost/asio/streambuf.hpp>

namespace http {
    namespace server {

        class CResponse {

        public:
            void FillBuffer(const std::string& path);
            void ResponseMessage(const std::string& message);
            boost::asio::streambuf& GetBuffer();

        private:
            boost::asio::streambuf m_buffer;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_RESPONSE_H
