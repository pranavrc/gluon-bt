project(Game)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

add_definitions(-DMAKE_BT_LIB)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../gluon-bt-common/ ${PROJECT_SOURCE_DIR}/../gluon-bt-lib/)

set(game_src
    main.cpp
    mainwindow.cpp
    game.cpp 
    gameitem.cpp 
    agent.cpp 
    go_up.cpp 
    go_right.cpp 
    go_left.cpp 
    go_down.cpp 
    btprobabilisticselectornode.cpp 
    enemy.cpp 
    btdebugnode.cpp 
    runner.cpp 
    btloopnode.cpp
    btwonnode.cpp 
    btparallelnode.cpp 
    worker.cpp 
    actions/stopmove.cpp 
    actions/relativeright.cpp 
    actions/relativeleft.cpp 
    actions/relativeforward.cpp 
    actions/relativeback.cpp 
    actions/movecloserupdown.cpp 
    actions/movecloserleftright.cpp 
    actions/moveawayupdown.cpp 
    actions/moveawayleftright.cpp 
    actions/iscollided.cpp 
    actions/btlearningnode.cpp 
    actions/btgoalnode.cpp 
    player.cpp 
    guard.cpp 
    scenario.cpp 
    scenarioset.cpp 
    actions/btnotnode.cpp
)


set(mainwindow_UIS
    mainwindow.ui
)
 
qt4_wrap_ui(mainwindow_UIS_H ${mainwindow_UIS})
 
qt4_automoc(${game_src})
add_executable(Game ${game_src} ${mainwindow_UIS_H})

find_library(LIBBT
    NAMES
        libbtlib.so
        libbtlib.dylib
        libbtlib.dll
    PATHS
        c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/ 
        /usr/lib
        /Users/kimjung/Uni/gluon-bt/src/gluon-bt-lib/build
)
message("-- Found libbtlib:" ${LIBBT})

find_path(LIBBTPATH
    NAMES
        libbtlib.so
        libbtlib.dylib
        libbtlib.dll
    PATHS
        c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/
        /usr/lib
        /Users/kimjung/Uni/gluon-bt/src/gluon-bt-lib/build
)
message("-- Found libbt's path:" ${LIBBTPATH})
add_library(btlib SHARED IMPORTED)
set_property(TARGET btlib PROPERTY IMPORTED_LOCATION ${LIBBT})
set_property(TARGET btlib PROPERTY IMPORTED_IMPLIB ${LIBBT})

target_link_libraries(Game ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY} btlib)
