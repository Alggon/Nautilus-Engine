cmake_minimum_required(VERSION 3.24)
project(NAUTILUS LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SDL3 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-3.2.0 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SDL3)

enable_testing()
add_subdirectory(Source)