# Setup source
set(SOURCE
	circularBufferDynamic.c
)

# Set header files
set(HEADER
    circularBufferDynamic.h
)

add_library(circularBufferDynamic STATIC
	${SOURCE}
    ${HEADER}
)

# Add gtests to project (Google Test framework for unit testing)
add_subdirectory(gtests)