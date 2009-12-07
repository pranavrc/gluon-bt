# -------------------------------------------------
# Project created by QtCreator 2009-11-13T00:31:17
# -------------------------------------------------
QT += testlib
TARGET = Game
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    game.cpp \
    gameitem.cpp \
    agent.cpp \
    go_up.cpp \
    go_right.cpp \
    go_left.cpp \
    go_down.cpp \
    btprobabilisticselectornode.cpp \
    enemy.cpp \
    btdebugnode.cpp \
    runner.cpp \
    btloopnode.cpp \
    btwonnode.cpp \
    btparallelnode.cpp \
    worker.cpp \
    actions/stopmove.cpp \
    actions/relativeright.cpp \
    actions/relativeleft.cpp \
    actions/relativeforward.cpp \
    actions/relativeback.cpp \
    actions/movecloserupdown.cpp \
    actions/movecloserleftright.cpp \
    actions/moveawayupdown.cpp \
    actions/moveawayleftright.cpp \
    actions/iscollided.cpp \
    actions/btlearningnode.cpp \
    actions/btgoalnode.cpp
HEADERS += mainwindow.h \
    game.h \
    gameitem.h \
    agent.h \
    go_up.h \
    go_right.h \
    go_left.h \
    go_down.h \
    btprobabilisticselectornode.h \
    enemy.h \
    btdebugnode.h \
    runner.h \
    btloopnode.h \
    btwonnode.h \
    btparallelnode.h \
    worker.h \
    actions/stopmove.h \
    actions/relativeright.h \
    actions/relativeleft.h \
    actions/relativeforward.h \
    actions/relativeback.h \
    actions/movecloserupdown.h \
    actions/movecloserleftright.h \
    actions/moveawayupdown.h \
    actions/moveawayleftright.h \
    actions/iscollided.h \
    actions/btlearningnode.h \
    actions/btgoalnode.h
INCLUDEPATH += ../gluon-bt-lib \
    ../gluon-bt-common
LIBS += ../gluon-bt-lib/qtcreator-build/libbtlib.dll
FORMS += mainwindow.ui
