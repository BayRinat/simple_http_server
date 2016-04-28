/*++

Abstract:
  ConnectionManager class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_CONNECTIONMANAGER_H
#define HTTP_SERVER_CONNECTIONMANAGER_H

#include <set>
#include <boost/noncopyable.hpp>
#include "Connection.h"

namespace http {
    namespace server {

        class CConnectionManager
                : private boost::noncopyable {

        public:
            void Start(connection_ptr ptr);
            void Stop(connection_ptr ptr);
            void StopAll();

        private:
            std::set<connection_ptr> m_connections;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_CONNECTIONMANAGER_H
