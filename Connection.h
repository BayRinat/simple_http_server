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
#include <iostream>
#include <fstream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Request.h"

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

            boost::asio::ip::tcp::socket& GetSocket();

        private:
            void AsyncWrite(const char* data, size_t size);
            void AsyncWrite(const std::string& message);

            void OpenFile(const std::string &path);

            static constexpr size_t READ_BUFFER_SIZE = 1024;
            static constexpr size_t WRITE_BUFFER_SIZE = 1024;

            char m_read_buffer[READ_BUFFER_SIZE];
            char m_write_buffer[WRITE_BUFFER_SIZE];

            boost::asio::io_service::strand m_strand;
            boost::asio::ip::tcp::socket m_socket;
            CConnectionManager& m_connection_manager;

            const std::string& m_folder;

            CRequest m_request;
            std::ifstream m_file_stream;
        };

        using connection_ptr = boost::shared_ptr<CConnection>;

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_CONNECTION_H