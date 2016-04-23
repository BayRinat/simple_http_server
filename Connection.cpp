/*++

Abstract:
  Connection class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include "Connection.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ConnectionManager.h"
#include "ResponseMessages.h"

namespace http {
    namespace server {

        CConnection::CConnection(boost::asio::io_service& service, CRequest& handler,
                                 CConnectionManager& connection_manager, const std::string& folder)
                : m_socket(service), m_connection_manager(connection_manager), m_folder(folder) {
        };

        void CConnection::Start() {
            m_socket.async_read_some(m_request.GetBuffer().prepare(READ_BUF_SIZE),
                                     boost::bind(&CConnection::OnReadHandler, shared_from_this(),
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
        }

        void CConnection::Stop() {
            m_socket.close();
        }

        void CConnection::OnReadHandler(const boost::system::error_code& ec, std::size_t bytes_transferred) {
            if (!ec) {
                m_request.GetBuffer().commit(bytes_transferred);
                m_request.ParseStartLine();
                if (m_request.ParseStartLine())
                    m_response.FillBuffer(m_folder + m_request.GetUri());
                else
                    m_response.ResponseMessage(message::BAD_REQUEST);

                boost::asio::async_write(m_socket, m_response.GetBuffer().data(),
                                         boost::bind(&CConnection::OnWriteHandler, shared_from_this(),
                                                     boost::asio::placeholders::error,
                                                     boost::asio::placeholders::bytes_transferred));

            }
            else {
                m_connection_manager.Stop(shared_from_this());
            }
        }

        void CConnection::OnWriteHandler(const boost::system::error_code& ec, std::size_t bytes_transferred) {
            if (!ec) {
                m_response.GetBuffer().consume(bytes_transferred);
                boost::system::error_code ignored_ec;
                m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
            }

            if (ec != boost::asio::error::operation_aborted) {
                m_connection_manager.Stop(shared_from_this());
            }
        }

        boost::asio::ip::tcp::socket& CConnection::GetSocket() {
            return m_socket;
        }

    } // namespace server
} // namespace http