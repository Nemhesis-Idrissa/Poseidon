project(AegisData)


# ========================================
# Source Files
# ========================================

set(HEADERS
    UserDatabase.h
)


set(SOURCES
    UserDatabase.cpp
)

# ========================================
# Create Library
# ========================================
add_library(AegisData STATIC
    ${HEADERS}
    ${SOURCES}
)

# ========================================
# Include Directories
# ========================================
target_include_directories(AegisData PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# ========================================
# Link Libraries
# ========================================
target_link_libraries(AegisData PUBLIC
    Qt6::Widgets
    Qt6::Core
)
