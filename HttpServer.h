/*++

Abstract:
  HttpServer class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_SERVER_H
#define HTTP_SERVER_SERVER_H

#include <boost/asio.hpp>
#include "Acceptor.h"
#include "Connection.h"
#include "ConnectionManager.h"


namespace http {
    namespace server {

        class CHttpServer {
        public:

            explicit CHttpServer(const std::string& address, const std::string& port, const std::string& folder);

            void Start();
            void Stop();
            void Run();

            void OnAcceptedHandler(const boost::system::error_code& ec);

        private:
            void ServiceRun();

            static constexpr int THREADS_COUNT = 4;

            boost::asio::io_service m_service;
            // work object prevents io_service from being stopped when out of work
            boost::asio::io_service::work m_service_work;
            CAcceptor m_acceptor;
            std::string m_folder;

            CRequest m_request_handler;

            boost::shared_ptr<CConnection> m_connection_ptr;
            CConnectionManager m_connections_array;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_SERVER_H
