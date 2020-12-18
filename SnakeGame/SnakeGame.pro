QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Food.cpp \
    GameWindow.cpp \
    Snake.cpp \
    main.cpp \
    mainwindow.cpp \
    pvpgame.cpp \
    setting_scene.cpp \
    wall.cpp

HEADERS += \
    Food.h \
    GameWindow.h \
    Snake.h \
    mainwindow.h \
    pvpgame.h \
    setting_scene.h \
    wall.h

FORMS += \
    GameWindow.ui \
    mainwindow.ui \
    pvpgame.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

