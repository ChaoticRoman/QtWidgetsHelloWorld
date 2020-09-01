QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    FruitListModel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FruitListModel.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
