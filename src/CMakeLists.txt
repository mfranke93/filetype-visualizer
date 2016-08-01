include_directories(${VISUALIZER_SOURCE_DIR}/src)
link_directories(${VISUALIZER_BINARY_DIR}/src)

add_executable(main main.cpp
                    io/filereader.cpp
                    io/bmp_writer.cpp
                    data/grid.cpp
                    data/histogram.cpp
                    vis/hist_text.cpp
              )
#target_link_libraries(cdemo m) #link the math library
