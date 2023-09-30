cmake_minimum_required(VERSION 3.5)

project(ocv_tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui tracking)

add_executable(ocv_tracker main.cpp player.h player.cpp trackerservice.h trackerservice.cpp csvwriter.h csvwriter.cpp)
target_link_libraries(ocv_tracker ${OpenCV_LIBS})

install(TARGETS ocv_tracker LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
