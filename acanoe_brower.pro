#-------------------------------------------------
#
# Project created by QtCreator 2013-11-18T17:56:49
#
#-------------------------------------------------


QT       += core gui
QT += sql

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:LIBS += -lsetupapi
LIBS += -lws2_32


INCLUDEPATH += $$quote(Z:\share\code\qt\acanoe_brower\include)
INCLUDEPATH += C:\inc

LIBS += $$quote(Z:\share\code\qt\acanoe_brower\lib\libgmp.a)
LIBS += $$quote(Z:\share\code\qt\acanoe_brower\lib\libgmpxx.a)

CONFIG += qaxcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = acanoe_brower
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    title_widget.cpp \
    content_widget.cpp \
    push_button.cpp \
    sqlapi.cpp \
    configure.cpp \
    toolswidget.cpp \
    system_tray.cpp \
    input_dialg.cpp \
    gmpmath.cpp \
    main_menu.cpp \
    test.cpp \
    excelengine.cpp

HEADERS  += mainwindow.h \
    title_widget.h \
    content_widget.h \
    push_button.h \
    sqlapi.h \
    configure.h \
    toolswidget.h \
    system_tray.h \
    about_us.h \
    gmpmath.h \
    main_menu.h \
    test.h \
    excelengine.h

RESOURCES += \
    QRC.qrc

OTHER_FILES += \
    storage.rc
RC_FILE = \
    storage.rc
