QT += core gui widgets

TARGET = twi
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           tworld.cpp \
           headerwidget.cpp

HEADERS += mainwindow.h \
           tworld.h \
           luts.h \
           headerwidget.h

RESOURCES += ressources.qrc

OTHER_FILES += .gitignore \
               LICENSE \
               README.md

CONFIG += c++11
