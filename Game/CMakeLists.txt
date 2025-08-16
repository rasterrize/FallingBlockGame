cmake_minimum_required(VERSION 3.10.0)
project(fbg-game VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} fbg-core)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "FallingBlockGame")