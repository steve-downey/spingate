set(test_sources
  test1.cpp
  spingate.t.cpp
  batch.t.cpp
  sample.t.cpp
  experiment.t.cpp
  litmus_tests.cpp
)
add_executable(spintest ${test_sources})

target_link_libraries(spintest
  gtest_main
  spingate)

include(GoogleTest)

gtest_discover_tests(spintest)
