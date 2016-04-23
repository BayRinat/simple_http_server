/*++

Abstract:
  Connection class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_CONNECTION_H
#define HTTP_SERVER_CONNECTION_H

#include <cstdio>
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Request.h"
#include "Response.h"

namespace http {
    namespace server {

        class CConnectionManager;

        class CConnection
                : public boost::enable_shared_from_this<CConnection>,
                  private boost::noncopyable {

        public:
            explicit CConnection(boost::asio::io_service& service, CRequest& handler,
                                 CConnectionManager& connection_manager, const std::string& folder);

            void Start();
            void Stop();
            void OnReadHandler(const boost::system::error_code& ec,
                               std::size_t bytes_transferred);
            void OnWriteHandler(const boost::system::error_code& ec,
                                std::size_t bytes_transferred);

            boost::asio::ip::tcp::socket& GetSocket();

        private:
            static constexpr size_t READ_BUF_SIZE = 102400; // 100KB

            boost::asio::ip::tcp::socket m_socket;
            CConnectionManager& m_connection_manager;
            const std::string& m_folder;

            CRequest m_request;
            CResponse m_response;
        };

        using connection_ptr = boost::shared_ptr<CConnection>;

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_CONNECTION_H