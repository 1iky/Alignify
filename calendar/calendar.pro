QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calendar.cpp \
    calendarmanager.cpp \
    calendarstyle.cpp \
    event.cpp \
    eventactions.cpp \
    eventbuilder.cpp \
    eventdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    user.cpp \
    usermanager.cpp

HEADERS += \
    calendar.h \
    calendarmanager.h \
    calendarstyle.h \
    event.h \
    eventactions.h \
    eventbuilder.h \
    eventdialog.h \
    mainwindow.h \
    person.h \
    user.h \
    usermanager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
