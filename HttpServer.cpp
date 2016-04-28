/*++

Abstract:
  HttpServer class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include "HttpServer.h"
#include <boost/thread.hpp>

namespace http {
    namespace server {

        CHttpServer::CHttpServer(const std::string& address, const std::string& port, const std::string& folder)
                : m_service(), m_service_work(m_service), m_acceptor(m_service, address, port), m_folder(folder) {

            Start();
        }

        void CHttpServer::Start() {
            m_connection_ptr.reset(new CConnection(m_service, m_request_handler, m_connections_array, m_folder));
            m_acceptor.GetAcceptor().async_accept(m_connection_ptr->GetSocket(),
                                                  boost::bind(&CHttpServer::OnAcceptedHandler,
                                                              this, boost::asio::placeholders::error));
        }

        void CHttpServer::Stop() {
            m_service.stop();
        }

        void CHttpServer::Run() {
            for(auto i = 0; i < THREADS_COUNT; ++i) {
                m_threads_group.create_thread(boost::bind(
                        &boost::asio::io_service::run, &m_service));
            }
            m_threads_group.join_all();
        }

        void CHttpServer::OnAcceptedHandler(const boost::system::error_code& ec) {
            if (ec == boost::system::errc::success) {
                m_connections_array.Start(m_connection_ptr);
                Start();
            }
            else {
                m_acceptor.GetAcceptor().close();
                m_connections_array.StopAll();
            }
        }

    } // namespace server
} // namespace http













