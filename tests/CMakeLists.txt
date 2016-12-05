include_directories(${gtest_SOURCE_DIR}/include)
set(test_sources
  test1.cpp
  spingate.t.cpp
  batch.t.cpp
  sample.t.cpp
)
add_executable(spintest ${test_sources})
target_link_libraries(spintest gtest_main spingate)
add_test(NAME SpinTest COMMAND spintest)
