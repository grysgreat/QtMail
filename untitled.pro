#-------------------------------------------------
#
# Project created by QtCreator 2022-03-06T14:58:30
#
#-------------------------------------------------
QT       += core gui axcontainer concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    emailWgt.cpp \
        main.cpp \
        mainwindow.cpp \
    infrom.cpp \
    checkmail.cpp \
    sendmail.cpp\
    toast.cpp \
 util.cpp\
 Email.cpp\
Exception.cpp\
TCPConnector.cpp\
 MIMEContent.cpp\
    STMPConnector.cpp\
 POP3Connector.cpp\
User.cpp \
    qmailbegin.cpp
HEADERS += \
    emialWgt.h \
       mainwindow.h \
    infrom.h \
    checkmail.h \
    sendmail.h\
    toast.h \
    util.h\
        Email.h\
        Exception.h\
        TCPConnector.h\
        MIMEContent.h\
        POP3Connector.h\
        STMPConnector.h\
        User.h \
    qmailbegin.h\
    json.hpp


FORMS += \
    emailWgt.ui \
        mainwindow.ui \
    infrom.ui \
    checkmail.ui \
    sendmail.ui \
    qmailbegin.ui



LIBS +=  -lws2_32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc\
    loading.gif

DISTFILES +=
