cmake_minimum_required(VERSION 2.6)
project(VISUALIZER)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
#find_package(GLUT)
#find_package(OpenGL)

SET(CONFIGURATION Release)
SET(CMAKE_INSTALL_PREFIX /usr/local)
SET (EXECUTABLE_OUTPUT_PATH
   ${PROJECT_BINARY_DIR}
   CACHE PATH
   "Single Directory for all Executables."
   )

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -O3 -std=c++11")
add_subdirectory(man)
add_subdirectory(src)
add_subdirectory(src/tests)
