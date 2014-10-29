#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T17:16:18
#
#-------------------------------------------------

QT       += widgets

TARGET = BasicExporter
TEMPLATE = lib

DEFINES += BASICEXPORTER_LIBRARY

SOURCES += basicexporter.cpp \
    exportsettings.cpp

HEADERS += basicexporter.h\
        basicexporter_global.h \
    exportsettings.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    exportsettings.ui
