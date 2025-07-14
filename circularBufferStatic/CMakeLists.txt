
add_library(circularBufferStatic STATIC
	circularBufferStatic.c
    circularBufferStatic.h
)

target_include_directories(circularBufferStatic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)