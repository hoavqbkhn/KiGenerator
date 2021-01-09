QT += quick
QT += core widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    kiapp.cpp \
    action/actionprovider.cpp \
    logger/logger.cpp \
    common.cpp \
    processor/mainbusinessprocessor.cpp \
    processor/processorabstract.cpp \
    processor/workerthread.cpp \
    model/dataprocessor.cpp \
    model/officer.cpp \
    store/kiappstore.cpp \
    middleware/kimiddleware.cpp \
    model/officermodel.cpp \
    model/innermessage.cpp \
    model/resultmodelorderstyle.cpp \
    model/resultmodelkigroupstyle.cpp \
    model/createkimethod.cpp \
    model/adjustkimethod.cpp \
    model/kigeneratorhelper.cpp

RESOURCES += qml.qrc
#xlsx
QXLSX_PARENTPATH=./
QXLSX_HEADERPATH=./Xlsx/
QXLSX_SOURCEPATH=./Xlsx/
include(./QXlsx.pri)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    officer.h \
    kiapp.h \
    action/actionprovider.h \
    action/actiontype.h \
    logger/logger.h \
    common.h \
    processor/mainbusinessprocessor.h \
    processor/processorabstract.h \
    processor/workerthread.h \
    middleware/kiappmiddleware.h \
    middleware/kiappmiddlewareinterface.h \
    model/dataprocessor.h \
    model/officer.h \
    store/kiappstore.h \
    flux/action.h \
    flux/dispatcher.h \
    flux/middleware.h \
    flux/store.h \
    model/innermessage.h \
    model/setdefaultkimodel.h \
    model/resultmodelorderstyle.h \
    model/resultmodelkigroupstyle.h \
    model/createkimethod.h \
    model/adjustkimethod.h \
    model/kigeneratorhelper.h

DISTFILES += \
    logger/spdlog/contrib/README.md \
    logger/spdlog/fmt/bundled/LICENSE.rst \
    common/CustomDialog.qml \
    common/MyButton.qml \
    common/MyGroupBox.qml \
    common/ProgressButton.qml \
    common/ProgressCircle.qml \
    common/TabButton.qml
