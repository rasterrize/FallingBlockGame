cmake_minimum_required(VERSION 3.10.0)
project(fbg VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp src/Game.h src/Game.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "FallingBlockGame")

# Add pxl to project
include(FetchContent)

FetchContent_Declare(
    pxlFramework
    GIT_REPOSITORY https://github.com/rasterrize/pxlFramework
)

FetchContent_MakeAvailable(pxlFramework)
target_link_libraries(${PROJECT_NAME} pxlFramework)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)