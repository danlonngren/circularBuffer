# Setup test executable
add_executable(circularBufferDynamicTests 
    circularBufferDynamicTests.cpp
)

target_link_libraries(circularBufferDynamicTests 
    PRIVATE 
        GTest::gtest_main
        circularBufferDynamic
)

target_include_directories(circularBufferDynamicTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/circularBufferDynamic

)

include(GoogleTest)
gtest_discover_tests(circularBufferDynamicTests)