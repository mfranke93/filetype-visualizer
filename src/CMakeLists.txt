FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

FIND_PACKAGE(PNG REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})

include_directories(${VISUALIZER_SOURCE_DIR}/src)
link_directories(${VISUALIZER_BINARY_DIR}/src)

SET(BINARY_NAME ftvis)

add_executable(${BINARY_NAME}
                    main.cpp
                    io/filereader.cpp
                    io/png_writer.cpp
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

TARGET_LINK_LIBRARIES(${BINARY_NAME} ${Boost_LIBRARIES} ${PNG_LIBRARIES})

INSTALL(TARGETS ${BINARY_NAME}
    RUNTIME DESTINATION bin
    CONFIGURATIONS Release
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
