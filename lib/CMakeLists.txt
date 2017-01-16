set(spingate_sources
  spingate.cpp
  cvgate.cpp
  batch.cpp
  sample.cpp)

add_library(spingate STATIC ${spingate_sources})

target_link_libraries(spingate tupleutil)

target_include_directories(spingate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
