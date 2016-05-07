/*++

Abstract:
  Connection class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include "Connection.h"
#include <boost/bind.hpp>
#include "ConnectionManager.h"
#include "ResponseMessages.h"

namespace http {
    namespace server {

        CConnection::CConnection(boost::asio::io_service &service, CRequest &handler,
                                 CConnectionManager &connection_manager, const std::string &folder)
                : m_strand(service), m_socket(service), m_connection_manager(connection_manager), m_folder(folder) {
        };

        void CConnection::Start() {
            m_socket.async_read_some(boost::asio::buffer(m_read_buffer, READ_BUFFER_SIZE),
                                     m_strand.wrap(
                                             [this](boost::system::error_code ec,
                                                    std::size_t bytes_transferred) {
                                                 if (!ec) {
                                                     if (m_request.EndRequest(m_read_buffer, bytes_transferred)) {
                                                         if (m_request.ParseStartLine()) {
                                                             OpenFile(m_folder + m_request.GetUri());
                                                         }
                                                         else
                                                             AsyncWrite(message::BAD_REQUEST);
                                                     }
                                                     else
                                                         // request isn't complete, need more data
                                                         Start();
                                                 }
                                                 else
                                                     m_connection_manager.Stop(shared_from_this());
                                             }));
        }

        void CConnection::Stop() {
            boost::system::error_code ignored_ec;
            m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
            m_socket.close();
        }

         void CConnection::AsyncWrite(const std::string& message) {
            AsyncWrite(message.c_str(), message.size());
        }

        void CConnection::AsyncWrite(const char* data, size_t size) {
            m_socket.async_write_some(boost::asio::buffer(data, size),
                                      m_strand.wrap(
                                              [this](boost::system::error_code ec,
                                                     std::size_t bytes_transferred) {
                                                  if (!ec) {
                                                      // try to read part of file
                                                      if (m_file_stream.read(
                                                              m_write_buffer, WRITE_BUFFER_SIZE).gcount() > 0) {
                                                          AsyncWrite(m_write_buffer, m_file_stream.gcount());
                                                      }
                                                      else {
                                                          m_connection_manager.Stop(shared_from_this());
                                                      }
                                                  }
                                                  else
                                                      m_connection_manager.Stop(shared_from_this());
                                              }));
        }

        boost::asio::ip::tcp::socket &CConnection::GetSocket() {
            return m_socket;
        }

        void CConnection::OpenFile(const std::string &path) {
            m_file_stream = std::ifstream(path, std::ifstream::binary);
            try {
                if (m_file_stream) {
                    AsyncWrite(message::OK);
                }
                else
                    AsyncWrite(message::NOT_FOUND);
            }
            catch (std::exception &e) {
                std::cerr << e.what();
                m_connection_manager.Stop(shared_from_this());
            }
        }

    } // namespace server
} // namespace http












