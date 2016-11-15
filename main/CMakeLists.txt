add_executable(spin main.cpp)
target_link_libraries(spin spingate Threads::Threads)

add_executable(cv cvmain.cpp)
target_link_libraries(cv spingate Threads::Threads)
