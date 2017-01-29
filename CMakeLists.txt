cmake_minimum_required(VERSION 2.8.11)

project(ma_tricks)


# Find the QtWidgets library
find_package(Qt5Widgets)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(HEADER_FILES
        hdr/field.h
        hdr/helper.h
        hdr/main_win.h
        hdr/math_module.h
        hdr/set_dim.h
        hdr/simple_math.h)

set(SOURCE_FILES
        src/field.cpp
        src/main.cpp
        src/main_win.cpp
        src/set_dim.cpp
        src/simple_math.cpp)

QT5_WRAP_UI(UIS_HDRS
        forms/main_view.ui
        forms/set_dim.ui
        )

include_directories(${Qt5Widgets_LIBRARIES})
include_directories(${PROJECT_HEADER_FILES})

# on Linux
include_directories("/usr/include/eigen3/")
# on osx
include_directories("/usr/local/include/eigen3/")


add_executable(ma_tricks ${SOURCE_FILES} ${HEADER_FILES} ${UIS_HDRS})

target_link_libraries(ma_tricks Qt5::Widgets)
