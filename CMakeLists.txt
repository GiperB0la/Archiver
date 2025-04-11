cmake_minimum_required(VERSION 3.10)
project(Archiver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_library(ZSTD_LIBRARY zstd REQUIRED)
find_path(ZSTD_INCLUDE_DIR zstd.h REQUIRED)

add_executable(Archiver
    Main.cpp
    src/Archiver.cpp
)

target_include_directories(Archiver PRIVATE ${ZSTD_INCLUDE_DIR})
target_link_libraries(Archiver PRIVATE ${ZSTD_LIBRARY})

# sudo apt install libzstd-dev