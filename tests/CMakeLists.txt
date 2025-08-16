# tests/CMakeLists.txt

# Glob test sources
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

# Test executable (uses Catch2WithMain)
add_executable(mve_tests ${TEST_SOURCES})

# Link test binary with main code + test framework
target_link_libraries(mve_tests
    PRIVATE
        mve
        Catch2::Catch2WithMain
        spdlog::spdlog
)

target_include_directories(mve_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        sdplog::spdlog
)


# Test discovery integration
include(CTest)
include(Catch)
catch_discover_tests(mve_tests)
