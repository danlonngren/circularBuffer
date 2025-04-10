if (BUILD_TESTING)
    # Include the circularBufferStatic library
    include_directories(${CMAKE_SOURCE_DIR}/circularBufferDynamic)

    set(SOURCES
        circularBufferDynamicTests.cpp
    )

    # Setup test executable
    add_executable(circularBufferDynamicTests 
        ${SOURCES}
    )
    
    target_link_libraries(circularBufferDynamicTests PUBLIC 
        GTest::gtest_main
        circularBufferDynamic
    )

    add_test(
        NAME circularBufferDynamicTests
        COMMAND circularBufferDynamicTests
    )
    
endif()