add_library(circularBufferDynamic STATIC
	circularBufferDynamic.c
    circularBufferDynamic.h
)

target_include_directories(circularBufferDynamic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)