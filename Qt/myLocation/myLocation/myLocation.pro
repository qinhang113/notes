TEMPLATE = app

QT += qml quick
QT += core
QT += widgets
QT += positioning
QT += network sql


SOURCES += main.cpp \
    getlocation.cpp \
    losql.cpp

RESOURCES += qml.qrc \
    png.qrc \
    page.qrc \
    user.qrc \
    chart.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    getlocation.h \
    losql.h

DISTFILES +=
