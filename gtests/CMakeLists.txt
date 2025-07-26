include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0  # Use any tag, commit hash, or branch
)

# Prevent GoogleTest from overriding the parent project's compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(circularBufferStaticTests 
    circularBufferStaticTests.cpp
)

target_link_libraries(circularBufferStaticTests 
    PRIVATE 
        GTest::gtest_main
        circularBufferStatic
)

target_include_directories(circularBufferStaticTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/circularBufferStatic
)

include (GoogleTest)
gtest_discover_tests(circularBufferStaticTests)
