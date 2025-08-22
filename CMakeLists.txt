cmake_minimum_required(VERSION 3.16)
project(mveplayer LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -O0 -fno-omit-frame-pointer -D_GLIBCXX_ASSERTIONS)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)

find_package(SDL2 CONFIG REQUIRED)

# Add dependencies
CPMAddPackage("gh:catchorg/Catch2@3.5.2")
CPMAddPackage("gh:gabime/spdlog@1.13.0")
CPMAddPackage("gh:CLIUtils/CLI11#main")

# ImGui with SDL2 + OpenGL backend
CPMAddPackage(
  NAME imgui
  GITHUB_REPOSITORY ocornut/imgui
  VERSION 1.91.0
  DOWNLOAD_ONLY YES
)

if(imgui_ADDED)
  add_library(imgui
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
  )
  target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
  )
  find_package(OpenGL REQUIRED)
  target_link_libraries(imgui PUBLIC SDL2::SDL2 OpenGL::GL)
endif()


list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")

add_subdirectory(src)
add_subdirectory(tests)

add_executable(mveplayer
 src/main.cpp
)

target_link_libraries(mveplayer
 PRIVATE
    mve
    SDL2::SDL2main
    spdlog::spdlog
    CLI11::CLI11
    imgui
)
