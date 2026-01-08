cmake_minimum_required(VERSION 3.19)
project(Aegis LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets gui multimedia multimediawidgets Xml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
qt_standard_project_setup()

add_subdirectory(design)
add_subdirectory(app)
add_subdirectory(libs/ui)
add_subdirectory(database)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
