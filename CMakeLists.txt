cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "generate_xml")
project(${PROJECT_NAME})

set(SRC main.cpp inputVideo.cpp generateXML.cpp)
add_executable(${PROJECT_NAME} ${SRC})

set(TINYXML2_LIB tinyxml2_lib)
add_library(${TINYXML2_LIB} STATIC tinyxml2.cpp)

target_link_libraries(${PROJECT_NAME} ${TINYXML2_LIB}  opencv_highgui)

set (CMAKE_CXX_FLAGS "-std=c++14")
