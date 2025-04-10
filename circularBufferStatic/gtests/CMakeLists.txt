if (BUILD_TESTING)
    # Include the circularBufferStatic library
    include_directories(${CMAKE_SOURCE_DIR}/circularBufferStatic)

    set(SOURCES
        circularBufferStaticTests.cpp
    )

    # Setup test executable
    add_executable(circularBufferStaticTests 
        ${SOURCES}
    )
    
    target_link_libraries(circularBufferStaticTests PUBLIC 
        GTest::gtest_main
        circularBufferStatic
    )

    # # Include gtest and all tests in executable
    # # Include GoogleTest module to enable test discovery and integration
    # include (GoogleTest)
    # gtest_discover_tests(circularBufferStaticTests)

    add_test(
        NAME circularBufferStaticTests
        COMMAND circularBufferStaticTests
    )
    
endif()