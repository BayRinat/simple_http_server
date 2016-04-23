/*++

Abstract:
  Response class

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include <fstream>
#include <iostream>
#include "Response.h"
#include "ResponseMessages.h"

namespace http {
    namespace server {

        void CResponse::FillBuffer(const std::string& path) {
            std::ifstream file_stream(path, std::ifstream::binary);
            try {
                if (file_stream) {
                    ResponseMessage(message::OK);
                    // get length of file:
                    file_stream.seekg(0, file_stream.end);
                    int length = file_stream.tellg();
                    file_stream.seekg(0, file_stream.beg);
                    auto out_data = boost::asio::buffer_cast<char *>(m_buffer.prepare(length));
                    file_stream.read(out_data, length);
                    m_buffer.commit(length);
                    file_stream.close();
                }
                else
                    ResponseMessage(message::NOT_FOUND);
            }
            catch (std::exception& e) {
                std::cerr << e.what();
                ResponseMessage(message::INTERNAL_SERVER_ERROR);
            }
        }

        void CResponse::ResponseMessage(const std::string& message) {
            m_buffer.consume(m_buffer.size());
            m_buffer.sputn(message.c_str(), message.size());
        }

        boost::asio::streambuf& CResponse::GetBuffer() {
            return m_buffer;
        }

    } // namespace server
} // namespace http








