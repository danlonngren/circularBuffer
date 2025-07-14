# Setup test executable
add_executable(circularBufferStaticTests 
    circularBufferStaticTests.cpp
)

target_link_libraries(circularBufferStaticTests 
    PUBLIC 
        GTest::gtest_main
        circularBufferStatic
)

target_include_directories(circularBufferStaticTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/circularBufferStatic
)

# Include gtest and all tests in executable
# Include GoogleTest module to enable test discovery and integration
include (GoogleTest)
gtest_discover_tests(circularBufferStaticTests)
