project(AegisUI)


# ========================================
# Source Files
# ========================================

set(HEADERS
    includes/mainwindow.h
    includes/widgets/NavigationBar.h
    includes/widgets/SearchBar.h
    includes/pages/HomePage.h
    includes/pages/SearchPage.h
)


set(SOURCES
    sources/mainwindow.cpp
    sources/widgets/NavigationBar.cpp
    sources/widgets/SearchBar.cpp
    sources/pages/HomePage.cpp
    sources/pages/SearchPage.cpp
)

# ========================================
# Create Library
# ========================================
add_library(AegisUI STATIC
    ${HEADERS}
    ${SOURCES}
)

# ========================================
# Include Directories
# ========================================
target_include_directories(AegisUI PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
)

# ========================================
# Link Libraries
# ========================================
target_link_libraries(AegisUI PUBLIC
    Qt6::Widgets
)


