project(btlib)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../gluon-bt-common/)

set(btlib_SRCS
	btcharacter.cpp
    btfactory.cpp
    btbrain.cpp
    btselectornode.cpp
    btsequencenode.cpp
	btnode.cpp
	btprobselectornode.cpp
	btparallelnode.cpp
)

set(btlib_HEADERS
	btcharacter.h
    btfactory.h
    btbrain.h
    btselectornode.h
    btsequencenode.h
    ../gluon-bt-common/btglobal.h
    btlib_export.h
    btlib.h
	btnode.h
	probnode.h
	btprobselectornode.h
	btparallelnode.h
)

add_definitions(-DMAKE_BT_LIB)

qt4_automoc(${btlib_SRCS})
add_library(btlib SHARED ${btlib_SRCS} ${btlib_UIS_H})

target_link_libraries(btlib ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY})

install(TARGETS btlib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

install(FILES
${btlib_HEADERS}
DESTINATION ${INCLUDE_INSTALL_DIR}/ COMPONENT Devel)