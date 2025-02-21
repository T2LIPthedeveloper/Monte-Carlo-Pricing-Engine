cmake_minimum_required(VERSION 3.10)
project(MonteCarloPricing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -pthread")

# Find spdlog
find_package(spdlog REQUIRED)

# Add executable for main application
add_executable(monte_carlo src/main.cpp src/monte_carlo.cpp)
target_include_directories(monte_carlo PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(monte_carlo PRIVATE spdlog::spdlog)

# Enable testing
enable_testing()

# Download and set up GoogleTest if not available
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(runTests tests/test_monte_carlo.cpp src/monte_carlo.cpp)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(runTests PRIVATE gtest gtest_main spdlog::spdlog pthread)
add_test(NAME MonteCarloTests COMMAND runTests)
