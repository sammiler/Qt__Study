QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = playmdk
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES     += main.cpp widget.cpp
HEADERS     += widget.h
FORMS       += widget.ui
CONFIG      += warn_off

INCLUDEPATH += $$PWD/mdk
include ($$PWD/mdk/mdk.pri)

!contains(DEFINES, mdkx) {
error("mdk need c++11")
}
