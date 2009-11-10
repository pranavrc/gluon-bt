project(driver)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)
 
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../gluon-bt-common/)
 
set(driver_SRCS
    main.cpp
    driver.cpp
    btprobabilisticselectornode.cpp
)

qt4_automoc(${driver_SRCS})

find_library(LIBBT
    NAMES
      libbtlib
    PATHS
    c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/
  )

find_path(LIBBTPATH
    NAMES
      libbtlib
    PATHS
    c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/
  )


add_library(btlib SHARED IMPORTED)
set_property(TARGET btlib PROPERTY IMPORTED_LOCATION ${LIBBTPATH})
set_property(TARGET btlib PROPERTY IMPORTED_IMPLIB ${LIBBT})


add_executable(driver ${driver_SRCS})
 

target_link_libraries(driver ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${LIBBT})
