cmake_minimum_required(VERSION 3.10)
project(OOP_LAB_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/code/include)

# Main executable
add_executable(${PROJECT_NAME} code/src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_tests test/test_main.cpp)
target_include_directories(${PROJECT_NAME}_tests PRIVATE ${CMAKE_SOURCE_DIR}/code/include)
target_link_libraries(${PROJECT_NAME}_tests 
    PRIVATE 
    gtest_main
    gtest
)
target_compile_options(${PROJECT_NAME}_tests PRIVATE -Wall -Wextra)
enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)

