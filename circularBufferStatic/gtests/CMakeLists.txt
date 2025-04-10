if (BUILD_TESTING)
    set(this circularBufferStaticTests)

    # Setup test executable
    add_executable(${this} circularBufferStaticTests.cpp)
    target_link_libraries(${this}  PRIVATE GTest::gtest_main)

    # Include gtest and all tests in executable
    include (GoogleTest)
    gtest_discover_tests(${this} )
endif()