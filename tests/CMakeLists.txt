enable_testing()

file(GLOB_RECURSE TEST_SOURCES *.cpp)

add_executable(mve_tests ${TEST_SOURCES})
target_link_libraries(mve_tests
  PRIVATE
    mve
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(mve_tests)
