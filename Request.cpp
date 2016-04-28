/*++

Abstract:
  Request class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include <boost/algorithm/string.hpp>
#include "Request.h"

namespace http {
    namespace server {

        const std::string CRequest::GET_METHOD = "GET";
        const std::string CRequest::END_REQUEST = "\r\n\r\n";

        bool CRequest::EndRequest(const char* buffer, size_t size) {
            m_request.append(buffer, size);
            size_t found = m_request.find(END_REQUEST);
            if(found != std::string::npos)
                return true;

            return false;
        }

        bool CRequest::ParseStartLine() {
            std::vector<std::string> words;
            boost::split(words, m_request, boost::is_any_of("\r\n "));
            if(words.size() < 3)
                return false;

            m_startline.method = words[0];
            m_startline.uri = words[1];
            m_startline.protocol = words[2];

            if (m_startline.method != GET_METHOD)
                return false;

            return true;
        }

        const std::string& CRequest::GetUri() const {
            return m_startline.uri;
        }

    } // namespace server
} // namespace http




