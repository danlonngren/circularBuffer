add_library(circularBuffer_app STATIC
    circularBuffer.c
)

target_include_directories(circularBuffer_app PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
