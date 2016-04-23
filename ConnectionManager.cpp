/*++

Abstract:
  ConnectionManager class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include <boost/bind.hpp>
#include "ConnectionManager.h"

namespace http {
    namespace server {

        void CConnectionManager::Start(connection_ptr ptr) {
            m_connections.insert(ptr);
            ptr->Start();
        }

        void CConnectionManager::Stop(connection_ptr ptr) {
            m_connections.erase(ptr);
            ptr->Stop();
        }

        void CConnectionManager::Stop_all() {
            std::for_each(m_connections.begin(), m_connections.end(),
                          boost::bind(&CConnection::Stop, _1));
            m_connections.clear();
        }

    } // namespace server
} // namespace http