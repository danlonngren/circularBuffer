# Setup source
set(SOURCE
	circularBufferStatic.c
)

# Set header files
set(HEADER
    circularBufferStatic.h
)

add_library(circularBufferStatic STATIC
	${SOURCE}
    ${HEADER}
)

# Add gtests to project (Google Test framework for unit testing)
add_subdirectory(gtests)
