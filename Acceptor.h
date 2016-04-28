/*++

Abstract:
  Acceptor class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_ACCEPTOR_H
#define HTTP_SERVER_ACCEPTOR_H

#include <string>
#include <boost/asio/ip/tcp.hpp>

namespace http {
    namespace server {
        class CAcceptor {

        public:
            explicit CAcceptor(boost::asio::io_service& service, const std::string& address, const std::string& port);

            boost::asio::ip::tcp::acceptor& GetAcceptor();

        private:
            boost::asio::ip::tcp::acceptor m_acceptor;
            std::string m_address;
            std::string m_port;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_ACCEPTOR_H
