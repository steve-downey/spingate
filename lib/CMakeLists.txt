add_library(spingate STATIC spingate.cpp cvgate.cpp)
target_include_directories(spingate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
