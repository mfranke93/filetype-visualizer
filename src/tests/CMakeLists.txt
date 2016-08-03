include_directories(${VISUALIZER_SOURCE_DIR}/src/tests)
link_directories(${VISUALIZER_BINARY_DIR}/src/tests)

add_executable(tests tests.cpp 
                    test_grid.cpp 
                    test_histogram.cpp
                    test_hist_text.cpp
                    test_linear_normalizer.cpp
                    test_logarithmic_plus_one_normalizer.cpp
                    ../data/grid.cpp
                    ../data/histogram.cpp
                    ../data/linear_normalizer.cpp
                    ../data/logarithmic_plus_one_normalizer.cpp
                    ../vis/hist_text.cpp
              )
#target_link_libraries(cdemo m) #link the math library
