project(driver)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)
 
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../gluon-bt-common/)
 
set(driver_SRCS
    main.cpp
    driver.cpp
    btprobabilisticselectornode.cpp
    btdebug1node.cpp
    btdebug2node.cpp
    btblockernode.cpp
)


qt4_automoc(${driver_SRCS})

if(APPLE)

find_library(LIBBT
    NAMES
      libbtlib.dylib
    PATHS
    /Users/kimjung/Uni/gluon-bt/src/gluon-bt-lib/build/Debug/
    
  )

 
elseif()

find_library(LIBBT
    NAMES
      libbtlib
    PATHS
    c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/
    
  )

endif()

add_executable(driver ${driver_SRCS})
 

target_link_libraries(driver ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${LIBBT})
