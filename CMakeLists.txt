cmake_minimum_required(VERSION 3.28.3)
project(circularBufferApp LANGUAGES C CXX) 

option(BUILD_TESTS "Build sPIDController tests" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(circularBufferStatic)
add_subdirectory(circularBufferDynamic)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(external/googletest)
    add_subdirectory(circularBufferDynamic/gtests)
    add_subdirectory(circularBufferStatic/gtests)
endif()