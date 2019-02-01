cmake_minimum_required( VERSION 2.8.9 )

project( bezier )

include_directories( $CMAKE_SOURCE_DIR )

add_definitions(-std=c++11 )

set(SRCS
   #"ImageData.cpp"
   #"BresenhamLineDrawer.cpp"
   #"PNGRenderer.cpp"
   "main.cpp"
)

option(DEBUG_MACRO "Debug verbosity option" OFF)

if(DEBUG_MACRO)
   add_definitions(-DDEBUG)
endif()

add_executable( bezier "${SRCS}" )

target_link_libraries( bezier png z )

