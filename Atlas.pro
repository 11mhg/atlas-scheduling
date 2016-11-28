#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T20:48:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atlas
TEMPLATE = app


SOURCES += main.cpp\
    atlaswelcome.cpp \
    profile.cpp \
    weeklycalendar.cpp \
    taskcollapsed.cpp \
    taskexpanded.cpp \
    task.cpp \
    scheduler.cpp \
    weekheader.cpp \
    categorylist.cpp

HEADERS  += atlaswelcome.h \
    category.h \
    group.h \
    profile.h \
    scheduler.h \
    weeklycalendar.h \
    taskcollapsed.h \
    taskexpanded.h \
    task.h \
    weekheader.h \
    categorylist.h

FORMS    += atlaswelcome.ui \
    login.ui \
    newprofile.ui \
    profilecustomization.ui \
    addtask.ui \
    mycalendar.ui \
    mycharacter.ui \
    removetask.ui \
    settings.ui \
    mytreasurechest.ui \
    weeklycalendar.ui \
    taskexpanded.ui \
    weekheader.ui \
    categorylist.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../botan-master/ -lbotan
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../botan-master/ -lbotand

INCLUDEPATH += $$PWD/../botan-master/build/include
DEPENDPATH += $$PWD/../botan-master/build/include

RESOURCES += \
    itemresource.qrc \
    picresource.qrc \
    itemsfinal.qrc \
    ../Atlas-Builds/itemspart2.qrc
