/*++

Abstract:
  Acceptor class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include "Acceptor.h"

namespace http {
    namespace server {

        CAcceptor::CAcceptor(boost::asio::io_service& service, const std::string& address, const std::string& port)
                : m_acceptor(service), m_address(address), m_port(port) {
            boost::asio::ip::tcp::resolver resolver(service);
            boost::asio::ip::tcp::resolver::query query(m_address, m_port);
            boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
            m_acceptor.open(endpoint.protocol());
            m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            m_acceptor.bind(endpoint);
            m_acceptor.listen();
        }

        boost::asio::ip::tcp::acceptor& CAcceptor::GetAcceptor() {
            return m_acceptor;
        }

    } // namespace server
} // namespace http




