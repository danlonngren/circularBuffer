cmake_minimum_required(VERSION 3.28.3)
project(circularBufferApp LANGUAGES C CXX) 

add_library(circularBufferStatic STATIC
	circularBufferStatic.c
    circularBufferStatic.h
)

target_include_directories(circularBufferStatic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(circularBufferStatic PRIVATE c_std_99)
target_compile_features(circularBufferStatic PRIVATE cxx_std_17)

option(BUILD_TESTS "Build GoogleTests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(gtests)
endif()