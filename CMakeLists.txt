cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)

project(spdlog_fold_sink)

add_executable(spdlog_fold_sink
    src/main.cpp)

# 指定头文件目录
target_include_directories(spdlog_fold_sink PUBLIC include)

find_package(spdlog REQUIRED)

target_link_libraries(spdlog_fold_sink
    spdlog::spdlog)
