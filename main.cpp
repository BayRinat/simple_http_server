/*++

Abstract:
  main.cpp

Author:
  Rinat Baygildin (bayrinat@gmail.com)

--*/

#include <iostream>
#include "HttpServer.h"

int main(int argc, char* argv[]) {
    try {
        if (argc == 4) {
            http::server::CHttpServer server(argv[1], argv[2], argv[3]);
            server.Run();
        }
        else
            std::cerr << "Usage: http_server addreess port folder" << std::endl;

    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}