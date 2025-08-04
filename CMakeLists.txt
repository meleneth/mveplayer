cmake_minimum_required(VERSION 4.0.2)
project(mveplayer LANGUAGES CXX)

include(FindPkgConfig)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)

# Add dependencies
CPMAddPackage("gh:catchorg/Catch2@3.5.2")
CPMAddPackage("gh:gabime/spdlog@1.13.0")

list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")

pkg_check_modules(SDL3 REQUIRED sdl3)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(mveplayer
 src/main.cpp
)

target_include_directories(mveplayer
  PRIVATE
    ${SDL3_INCLUDE_DIRS}
    sdplog::spdlog
)

target_link_libraries(mveplayer
 PRIVATE
    mve
    ${SDL3_LIBRARIES}
    spdlog::spdlog
)

