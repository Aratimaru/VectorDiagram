QT       += core gui
QT          += core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    view/arrow.cpp \
    calculations/complexnumberadapter.cpp \
    main.cpp \
    view/diagramplot.cpp \
    view/diagramview.cpp \
    view/mainwindow.cpp \
    data_structure/phasevector.cpp \
    calculations/phasevectorcalculator.cpp \
    model/vectordiagrammodel.cpp \
    view/qcustomplot.cpp

HEADERS += \
    view/arrow.h \
    calculations/calculator.h \
    calculations/complexnumberadapter.h \
    view/diagramplot.h \
    view/diagramview.h \
    view/mainwindow.h \
    data_structure/phasevector.h \
    calculations/phasevectorcalculator.h \
    model/vectordiagrammodel.h \
    view/qcustomplot.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore