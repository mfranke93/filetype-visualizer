include_directories(${VISUALIZER_SOURCE_DIR}/src/tests)
link_directories(${VISUALIZER_BINARY_DIR}/src/tests)

add_executable(tests tests.cpp 
                    test_grid.cpp 
                    test_histogram.cpp
                    test_hist_text.cpp
                    test_linear_normalizer.cpp
                    test_logarithmic_plus_one_normalizer.cpp
                    test_image.cpp
                    test_image_builder.cpp
                    test_standard_colormap.cpp
                    test_standard_single_byte_transition_counter.cpp
                    test_filereader.cpp
                    ../data/grid.cpp
                    ../data/histogram.cpp
                    ../data/linear_normalizer.cpp
                    ../data/logarithmic_plus_one_normalizer.cpp
                    ../data/standard_single_byte_transition_counter.cpp
                    ../vis/hist_text.cpp
                    ../vis/image.cpp
                    ../vis/image_builder.cpp
                    ../vis/standard_colormap.cpp
                    ../io/filereader.cpp
              )
#target_link_libraries(cdemo m) #link the math library
