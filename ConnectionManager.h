/*++

Abstract:
  ConnectionManager class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#ifndef HTTP_SERVER_CONNECTIONMANAGER_H
#define HTTP_SERVER_CONNECTIONMANAGER_H


#include <boost/noncopyable.hpp>
#include <set>
#include "Connection.h"

namespace http {
    namespace server {

        class CConnectionManager
                : private boost::noncopyable {

        public:
            void Start(connection_ptr ptr);
            void Stop(connection_ptr ptr);
            void Stop_all();

        private:
            std::set<connection_ptr> m_connections;
        };

    } // namespace server
} // namespace http

#endif //HTTP_SERVER_CONNECTIONMANAGER_H
