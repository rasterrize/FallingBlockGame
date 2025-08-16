cmake_minimum_required(VERSION 3.10.0)
project(fbg-core VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC src/GameWindow.h src/GameWindow.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC src)

# This project uses CPM (CMake Package Manager)
include(../cmake/CPM.cmake)

# Add glfw to project
CPMAddPackage("gh:glfw/glfw#3.4")
target_link_libraries(${PROJECT_NAME} glfw)
