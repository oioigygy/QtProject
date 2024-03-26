QT       += core gui
QT       += sql
QT       += widgets
QT       += websockets
QT       += webenginewidgets
QT       +=  charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
msvc:QMAKE_CXXFLAGS += -source-charset:utf-8

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseinfo.cpp \
    basetitlebar.cpp \
    dashboard.cpp \
    database_manger.cpp \
    devicestatus.cpp \
    equipment.cpp \
    linemanage.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mytitlebar.cpp \
    peoplemanage.cpp \
    taskmanage.cpp \
    titlebarshow.cpp

HEADERS += \
    baseinfo.h \
    basetitlebar.h \
    dashboard.h \
    database_manger.h \
    devicestatus.h \
    equipment.h \
    linemanage.h \
    login.h \
    mainwindow.h \
    mytitlebar.h \
    peoplemanage.h \
    taskmanage.h \
    titlebarshow.h

FORMS += \
    baseinfo.ui \
    devicestatus.ui \
    equipment.ui \
    linemanage.ui \
    login.ui \
    mainwindow.ui \
    peoplemanage.ui \
    taskmanage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    images.qrc

DISTFILES += \
    C:/Users/oioigy/Desktop/login_image.png \
    echarts.min.js \
    echarts_test/gauge-stage.html \
    echarts_test/gauge-temperature.html \
    echarts_test/gauge.html \
    echarts_test/index.html \
    test.html
