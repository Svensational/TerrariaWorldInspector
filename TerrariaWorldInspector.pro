QT += core gui widgets

TARGET = twi
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           tworld.cpp

HEADERS += mainwindow.h \
           tworld.h \
           luts.h

RESOURCES += ressources.qrc

OTHER_FILES += .gitignore \
               LICENSE \
               README.md

CONFIG += c++11
