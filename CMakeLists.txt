cmake_minimum_required(VERSION 3.27)

project(
    sdb
    VERSION 0.1
    DESCRIPTION "simple database"
    # HOMEPAGE_URL https://github.com/hqn2/sdb.git
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(sdb src/main.cpp)

target_link_libraries(sdb PRIVATE sut )

add_library(sut
    src/freespace.cpp
    src/buffer.cpp
)

add_subdirectory(test)
