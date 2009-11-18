# -------------------------------------------------
# Project created by QtCreator 2009-11-13T00:31:17
# -------------------------------------------------
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
    runner.cpp
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
    runner.h
INCLUDEPATH += c:/repo/gluon-bt/src/gluon-bt-lib \
    c:/repo/gluon-bt/src/gluon-bt-common
LIBS += c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/libbtlib.dll
FORMS += mainwindow.ui
