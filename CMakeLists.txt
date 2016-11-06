cmake_minimum_required(VERSION 3.5)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project(SpingGate C CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(CTest)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ftemplate-backtrace-limit=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-inline -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -g0 -DNDEBUG")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(spingate main.cpp spingate.cpp)
target_link_libraries(spingate Threads::Threads)
