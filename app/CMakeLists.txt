project(AegisSecurityApp)

# ========================================
# Source Files
# ========================================
set(APP_SOURCES
    main.cpp
)

set(APP_UI
    mainwindow.ui
)

# ========================================
# Create Executable
# ========================================
qt_add_executable(AegisSecurity
    WIN32 MACOSX_BUNDLE
    ${APP_SOURCES}
    ${APP_UI}
)

# ========================================
# Include Root for Headers
# ========================================
target_include_directories(AegisSecurity PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# ========================================
# Link Qt
# ========================================
target_link_libraries(AegisSecurity PRIVATE
    Qt6::Core
    Qt6::Widgets
)


# ========================================
# Install
# ========================================
include(GNUInstallDirs)

install(TARGETS AegisSecurity
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET AegisSecurity
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
