/*++

Abstract:
  Request class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_REQUEST_H
#define HTTP_SERVER_REQUEST_H

namespace http {
    namespace server {

        struct SStartLine {
            std::string method;
            std::string uri;
            std::string protocol;
        };

        class CRequest {

        public:
            bool EndRequest(const char* buffer, size_t size);
            bool ParseStartLine();
            const std::string& GetUri() const;

        private:
            static const std::string GET_METHOD;
            static const std::string END_REQUEST;

            std::string m_request;
            SStartLine m_startline;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_REQUEST_H
