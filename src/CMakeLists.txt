# src/CMakeLists.txt

# Collect all source files under src/
file(GLOB_RECURSE MVEPLAYER_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Create the static library
add_library(mve STATIC ${MVEPLAYER_SOURCES})

# Public headers for use by other targets (e.g., tests)
target_include_directories(mve PRIVATE ${SDL3_INCLUDE_DIRS} sdplog::spdlog)
target_link_libraries(mve PRIVATE ${SDL3_LIBRARIES} spdlog::spdlog)

# Enable warnings (you can tweak to taste)
target_compile_options(mve PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)
