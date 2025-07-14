cmake_minimum_required(VERSION 3.28.3)
project(circularBufferApp LANGUAGES C CXX) 

# Enable use of VERSION in project()
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()

project(circularBufferApp VERSION 0.1.1 DESCRIPTION "Circular Buffers" LANGUAGES C CXX) 

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