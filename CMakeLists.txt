cmake_minimum_required(VERSION 3.5)

project(
  frpWall
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# openssl (set(OPENSSL_DIR  E:/cpplib/OpenSSL-Win64/bin) link_libraries(openssl
# libcrypto))
find_package(OpenSSL REQUIRED)

include_directories(app)
include_directories(E:/cpplib/yaml-cpp-yaml-cpp-0.7.0/include)
include_directories(E:/cpplib/boost_1_81_0)
include_directories(E:/cpplib/boost_1_81_0/boost/asio/ssl)
include_directories(E:/cpplib/OpenSSL-Win64/include)

set(PROJECT_SOURCES
    main.cpp
    app/yamlUtils.cpp
    app/yamlUtils.h
    app/logFilter.cpp
    app/logFilter.h
    app/asio_request.cpp
    app/asio_request.h
    app/file_operator.cpp
    app/file_operator.h
    ./include/xdb_searcher.cpp
    ./include/xdb_searcher.h
    # $service ./asio_http/connection_manager.cpp
    # ./asio_http/connection_manager.hpp ./asio_http/connection.cpp
    # ./asio_http/connection.hpp ./asio_http/reply.cpp ./asio_http/reply.hpp
    # ./asio_http/request.hpp ./asio_http/header.hpp ./asio_http/mime_types.cpp
    # ./asio_http/mime_types.hpp ./asio_http/request_handler.cpp
    # ./asio_http/request_handler.hpp ./asio_http/request_parser.cpp
    # ./asio_http/request_parser.hpp
)

add_executable(frpWall ${PROJECT_SOURCES})

target_link_libraries(frpWall
                      E:/cpplib/yaml-cpp-yaml-cpp-0.7.0/build/libyaml-cpp.a)
target_link_libraries(frpWall C:/Windows/System32/ws2_32.dll)
target_link_libraries(frpWall E:/cpplib/OpenSSL-Win64/bin/libcrypto-3-x64.dll)
target_link_libraries(frpWall E:/cpplib/OpenSSL-Win64/bin/libssl-3-x64.dll)

set_target_properties(
  frpWall
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE)
