QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Course.cpp \
    Homework.cpp \
    Remind.cpp \
    fix.cpp \
    fixcs.cpp \
    fixre.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Course.h \
    Homework.h \
    Remind.h \
    fix.h \
    fixcs.h \
    fixre.h \
    widget.h

FORMS += \
    fix.ui \
    fixcs.ui \
    fixre.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Memo-resource.qrc

