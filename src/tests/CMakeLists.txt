include_directories(${VISUALIZER_SOURCE_DIR}/src/tests)
link_directories(${VISUALIZER_BINARY_DIR}/src/tests)

add_executable(tests tests.cpp test_grid.cpp ../data/grid.cpp)
#target_link_libraries(cdemo m) #link the math library
