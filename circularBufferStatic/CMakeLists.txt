set(this circularBufferStatic)

# Setup source and header files
add_library(${this} STATIC
circularBuffer.c
)

target_include_directories(${this}  PUBLIC
${CMAKE_CURRENT_LIST_DIR}
)

# Add gtests to project
add_subdirectory(gtests)
