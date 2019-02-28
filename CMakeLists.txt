cmake_minimum_required( VERSION 3.1.0 )

project( bezier_curve )

include_directories( $CMAKE_SOURCE_DIR )

add_definitions(-std=c++11 )

set(EXEC_NAME "bezier_curve")

set(SRCS
   "PNGImageData.cpp"
   "ImageData.cpp"
   "BresenhamLineDrawer.cpp"
   "PNGRenderer.cpp"
   "BezierCurve.cpp"
   "main.cpp"
)

option(DEBUG_MACRO "Debug verbosity option" OFF)

if(DEBUG_MACRO)
   add_definitions(-DDEBUG)
endif()

add_executable( "${EXEC_NAME}" "${SRCS}" )

target_link_libraries( "${EXEC_NAME}" png z )

