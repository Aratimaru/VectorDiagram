QT       += core gui
QT          += core
QT += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    view/arrow.cpp \
    calculations/complexnumberadapter.cpp \
    main.cpp \
    view/cparrow.cpp \
    view/custom_widgets/customlabel.cpp \
    view/custom_widgets/customvlayout.cpp \
    view/custom_widgets/layoutgenerator.cpp \
    view/diagramplot.cpp \
    view/diagramview.cpp \
    view/diagramwindow.cpp \
    view/mainwindow.cpp \
    data_structure/phasevector.cpp \
    calculations/phasevectorcalculator.cpp \
    model/vectordiagrammodel.cpp \
    view/qcustomplot.cpp \
    view/widgetcreator.cpp

HEADERS += \
    view/arrow.h \
    calculations/calculator.h \
    calculations/complexnumberadapter.h \
    view/cparrow.h \
    view/custom_widgets/customlabel.h \
    view/custom_widgets/customvlayout.h \
    view/custom_widgets/layoutgenerator.h \
    view/diagramplot.h \
    view/diagramview.h \
    view/diagramwindow.h \
    view/mainwindow.h \
    data_structure/phasevector.h \
    calculations/phasevectorcalculator.h \
    model/vectordiagrammodel.h \
    view/qcustomplot.h \
    view/widgetcreator.h

FORMS += \
    view/diagramwindow.ui \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
