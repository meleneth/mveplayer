cmake_minimum_required(VERSION 3.25)
project(mveplayer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Enable CPM
FetchContent_Declare(
  CPM
  GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
  GIT_TAG origin/master
)
FetchContent_MakeAvailable(CPM)

# Add dependencies
CPMAddPackage("gh:catchorg/Catch2@3.5.2")
CPMAddPackage("gh:easylogging/easyloggingpp@v9.97.0")

add_subdirectory(src)
add_subdirectory(tests)
