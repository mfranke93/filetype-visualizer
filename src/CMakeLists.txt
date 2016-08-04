include_directories(${VISUALIZER_SOURCE_DIR}/src)
link_directories(${VISUALIZER_BINARY_DIR}/src)

add_executable(main main.cpp
                    io/filereader.cpp
                    io/bmp_writer.cpp
                    data/grid.cpp
                    data/histogram.cpp
                    data/standard_single_byte_transition_counter.cpp
                    data/linear_normalizer.cpp
                    data/logarithmic_plus_one_normalizer.cpp
                    vis/hist_text.cpp
                    vis/standard_colormap.cpp
              )
#target_link_libraries(cdemo m) #link the math library
