include_directories(${VISUALIZER_SOURCE_DIR}/src)
link_directories(${VISUALIZER_BINARY_DIR}/src)

add_executable(main main.cpp
                    io/filereader.cpp
                    data/grid.cpp
              )
#target_link_libraries(cdemo m) #link the math library
