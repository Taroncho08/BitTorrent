cmake_minimum_required(VERSION 3.10)
project(BitTorrentClient)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/BitTorrent.cpp
    src/Encoding.cpp
    src/FileItem.cpp
    src/InfoHashCalculator.cpp
    src/Parser.cpp
    src/TorrentFile.cpp
    src/TorrentFileBuilder.cpp
    src/Tracker.cpp
)

set(HEADERS
    include/BencodeValue.hpp
    include/BitTorrent.hpp
    include/Encoding.hpp
    include/FileItem.hpp
    include/InfoHashCalculator.hpp
    include/Parser.hpp
    include/TorrentFile.hpp
    include/TorrentFileBuilder.hpp
    include/Tracker.hpp
)

include_directories(include)

add_executable(BitTorrentClient ${SOURCES} src/main.cpp)

find_package(OpenSSL REQUIRED)
target_link_libraries(BitTorrentClient OpenSSL::Crypto)
