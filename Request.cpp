/*++

Abstract:
  Request class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include "Request.h"
#include <boost/algorithm/string.hpp>

namespace http {
    namespace server {

        const std::string CRequest::GET_METHOD = "GET";

        bool CRequest::ParseStartLine() {
            auto size = m_buffer.size();
            if (size == 0)
                return false;

            auto data = boost::asio::buffer_cast<const char *>(m_buffer.data());

            size_t spaces[2];
            size_t space_count{0};

            // find spaces
            for (auto i = 0; i < size; ++i) {
                if (data[i] == SP) {
                    spaces[space_count] = i;
                    ++space_count;
                }
                if(space_count == 2)
                    break;
            }
            // continue parsing data only in case spaces existence
            if (space_count != 0) {
                m_startline.method.assign(data, spaces[0]);
                m_startline.uri.assign(data + spaces[0] + 1, spaces[1] > 0 ? spaces[1] - spaces[0] - 1 : 0);
                // do not return '\r' and '\n' symbols
                size_t offset = 1;
                while (offset <= size &&
                       (data[size - offset] == LF)) {
                    ++offset;
                }
                m_startline.protocol.assign(data + spaces[1] + 1, size - spaces[1] - offset);
            }

            // check
            if (m_startline.method != GET_METHOD || m_startline.uri.size() == 0 || m_startline.protocol.size() == 0)
                return false;

            return true;
        }

        boost::asio::streambuf& CRequest::GetBuffer() {
            return m_buffer;
        }

        const std::string& CRequest::GetUri() const {
            return m_startline.uri;
        }

    } // namespace server
} // namespace http