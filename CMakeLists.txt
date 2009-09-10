project(bteditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

set(bteditor_SRCS
    btavailablenodestreeview.cpp
    bttreeeditor.cpp
    
    btbrain.cpp
    bteditor.cpp
    btnode.cpp
    btnodetype.cpp
    btnodetypesmodel.cpp
    btnodetypesmodelnode.cpp
    bttreemodel.cpp
	btactionnode.cpp
	btcompositenode.cpp
	btconditionnode.cpp
	btdecoratornode.cpp
	btreferencenode.cpp
	btunusablenode.cpp
	main.cpp
)

set(bteditor_UIS
    bteditor.ui
)

qt4_wrap_ui(bteditor_UIS_H ${bteditor_UIS})

qt4_automoc(${bteditor_SRCS})
add_executable(bteditor ${bteditor_SRCS} ${bteditor_UIS_H})

target_link_libraries(bteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
