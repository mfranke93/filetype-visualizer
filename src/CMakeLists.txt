FIND_PACKAGE(Boost 1.55 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

include_directories(${VISUALIZER_SOURCE_DIR}/src)
link_directories(${VISUALIZER_BINARY_DIR}/src)

add_executable(main main.cpp
                    io/filereader.cpp
                    io/bmp_writer.cpp
                    io/ppm_writer.cpp
                    data/grid.cpp
                    data/histogram.cpp
                    data/standard_single_byte_transition_counter.cpp
                    data/linear_normalizer.cpp
                    data/logarithmic_plus_one_normalizer.cpp
                    vis/hist_text.cpp
                    vis/standard_colormap.cpp
                    vis/image.cpp
                    vis/image_builder.cpp
                    cmdline/options.cpp
              )
TARGET_LINK_LIBRARIES(main ${Boost_LIBRARIES})
