/*++

Abstract:
  Request class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_REQUEST_H
#define HTTP_SERVER_REQUEST_H

#include <boost/asio/streambuf.hpp>

namespace http {
    namespace server {

        struct SStartLine {
            std::string method;
            std::string uri;
            std::string protocol;
        };

        class CRequest {

        public:
            bool ParseStartLine();
            boost::asio::streambuf& GetBuffer();
            const std::string& GetUri() const;

        private:
            static const std::string GET_METHOD;
            static constexpr const char LF = '\n';
            static constexpr const char SP = ' ';

            boost::asio::streambuf m_buffer;
            SStartLine m_startline;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_REQUEST_H