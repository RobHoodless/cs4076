`#-------------------------------------------------
#
# Project created by QtCreator 2017-02-11T19:33:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cs4076-dev
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
        game.cpp \
    entity.cpp \
    stationaryentity.cpp \
    item.cpp \
    door.cpp \
    mobileentity.cpp \
    player.cpp \
    room.cpp \
    gameview.cpp \
    collidableentity.cpp \
    enemy.cpp \
    map.cpp \
    mypixmap.cpp

HEADERS  += game.h \
    entity.h \
    stationaryentity.h \
    item.h \
    door.h \
    mobileentity.h \
    player.h \
    room.h \
    gameview.h \
    collidableentity.h \
    enemy.h \
    map.h \
    mypixmap.h \
    direction.h

FORMS    +=

RESOURCES += \
    res.qrc
