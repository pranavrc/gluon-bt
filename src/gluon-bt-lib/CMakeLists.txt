project(btlib)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

set(btlib_SRCS
    btnodetype.cpp
    btabstractfactory.cpp
    btnodetypefactory.cpp
    btselectornode.cpp
    main.cpp
)


qt4_automoc(${btlib_SRCS})
add_executable(btlib ${btlib_SRCS} ${btlib_UIS_H})

target_link_libraries(btlib ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
