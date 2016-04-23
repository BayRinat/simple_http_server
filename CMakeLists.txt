cmake_minimum_required(VERSION 3.5)
project(http_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# headers
set(HEADERS
        Acceptor.h
        Connection.h
        ConnectionManager.h
        HttpServer.h
        Request.h
        Response.h
        ResponseMessages.h)

# sources
set(SOURCES
        main.cpp
        Acceptor.cpp
        Connection.cpp
        ConnectionManager.cpp
        HttpServer.cpp
        Request.cpp
        Response.cpp)

include_directories(/home/rinat/boost_1_60_0)

link_directories(/home/rinat/boost_1_60_0/stage/lib)
link_directories(/usr/lib/x86_64-linux-gnu)
link_libraries(boost_thread)
link_libraries(boost_system)
link_libraries(boost_filesystem)
link_libraries(pthread)

add_executable(http_server ${HEADERS} ${SOURCES})