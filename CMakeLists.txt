cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME physics2)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(SOURCES main.cpp
        Circle.h)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)