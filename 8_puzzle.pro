QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    A_star.cpp \
    BFS.cpp \
    DFS.cpp \
    IDA_star.cpp \
    IDDFS.cpp \
    a_star_graph.cpp \
    advanced_analyse_tool.cpp \
    base.cpp \
    bfs_graph.cpp \
    bitmap.cpp \
    dfs_graph.cpp \
    graph_select.cpp \
    heu_func_select.cpp \
    ida_star_graph.cpp \
    iddfs_graph.cpp \
    main.cpp \
    eight_puzzle.cpp

HEADERS += \
    A_star.h \
    BFS.h \
    DFS.h \
    IDA_star.h \
    IDDFS.h \
    a_star_graph.h \
    advanced_analyse_tool.h \
    base.h \
    bfs_graph.h \
    bitmap.h \
    dfs_graph.h \
    eight_puzzle.h \
    graph_select.h \
    heu_func_select.h \
    ida_star_graph.h \
    iddfs_graph.h

FORMS += \
    eight_puzzle.ui

TRANSLATIONS += \
    8_puzzle_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

ICON = Icon.icns
