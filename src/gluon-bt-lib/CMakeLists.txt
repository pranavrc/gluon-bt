project(btlib)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../gluon-bt-common/)

set(btlib_SRCS
    ../gluon-bt-common/btnodetype.cpp
    ../gluon-bt-common/btnode.cpp
    ../gluon-bt-common/btcharacter.cpp
    btfactory.cpp
    btbrain.cpp
    btselectornode.cpp
    btsequencenode.cpp
)

set(btlib_HEADERS

    ../gluon-bt-common/btnodetype.h
    ../gluon-bt-common/btnode.h
    ../gluon-bt-common/btcharacter.h
    btfactory.h
    btbrain.h
    btselectornode.h
    btsequencenode.h
    ../gluon-bt-common/btglobal.h
    btlib_export.h
    btlib.h
)


add_definitions(-DMAKE_BT_LIB)

qt4_automoc(${btlib_SRCS})
add_library(btlib SHARED ${btlib_SRCS} ${btlib_UIS_H})

target_link_libraries(btlib ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY})

install(TARGETS btlib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(APPLE)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

endif()

install(FILES
${btlib_HEADERS}
DESTINATION ${INCLUDE_INSTALL_DIR}/ COMPONENT Devel)