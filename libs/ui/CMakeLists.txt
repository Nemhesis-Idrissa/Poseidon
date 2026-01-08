project(AegisUI)

set(CMAKE_AUTORCC ON)
# ========================================
# Source Files
# ========================================

set(HEADERS
    includes/mainwindow.h
    includes/widgets/NavigationBar.h
    includes/widgets/SearchBar.h
    includes/pages/HomePage.h
    includes/pages/SearchPage.h
    includes/pages/LoginScreen.h
)


set(SOURCES
    sources/mainwindow.cpp
    sources/widgets/NavigationBar.cpp
    sources/widgets/SearchBar.cpp
    sources/pages/HomePage.cpp
    sources/pages/SearchPage.cpp
    sources/pages/LoginScreen.cpp

)

set (RESOURCES images/resources.qrc)

# ========================================
# Create Library
# ========================================
add_library(AegisUI SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
)

# ========================================
# Include Directories
# ========================================
target_include_directories(AegisUI PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)



# ========================================
# Link Libraries
# ========================================
target_link_libraries(AegisUI PUBLIC
    Qt6::Widgets
    Qt6::Core
    AegisData
)


