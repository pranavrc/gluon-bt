project(bteditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(bteditor_SRCS bteditor.cpp main.cpp)
qt4_automoc(${bteditor_SRCS})
add_executable(bteditor ${bteditor_SRCS})
target_link_libraries(bteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
