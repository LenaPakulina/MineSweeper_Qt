QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app
DESTDIR = $$OUT_PWD/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell.cpp \
    config.cpp \
    diaabout.cpp \
    diasettings.cpp \
    grid.cpp \
    labelcust.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cell.h \
    config.h \
    diaabout.h \
    diasettings.h \
    grid.h \
    labelcust.h \
    mainwindow.h

FORMS += \
    diaabout.ui \
    diasettings.ui \
    mainwindow.ui

TRANSLATIONS = MineSweeper_en.ts

RC_ICONS = res/landMine.ico
DEFINES += PRO_RJ_PATH='\\"$${PWD}\\"'

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	res/res.qrc
