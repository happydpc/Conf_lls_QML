QT += quick
QT += serialport
QT += charts qml
QT += sql
QT += network
CONFIG+=qml_debug
CONFIG += c++17

TRANSLATIONS += QmlLanguage_ru.ts

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += PROGRESS
#DEFINES += GLOSSAV
#RC_FILE += icon_pg.rc
#RC_FILE += icon_gs.rc


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    connection/connectionFactory.cpp \
    device/deviceAbstract.cpp \
    device/devicesFactory.cpp \
    interfaces/interfacesAbstract.cpp \
    interfaces/interfaceSerial.cpp \
    command/commandController.cpp \
    other/crc.cpp \
    tests/testDevReply.cpp \
    view/module/treeitem.cpp \
    view/module/radialbar.cpp \
    device/Progress_TMK24/Progress_tmk24Data.cpp \
    device/Progress_TMK24/Progress_tmk24.cpp \
    device/Progress_TMK4UX/Progress_tmk4UXData.cpp \
    device/Progress_TMK4UX/Progress_tmk4UX.cpp \
    device/Progress_Base/Progress_BaseData.cpp \
    device/Progress_Base/progress_base_data.cpp \
    device/Progress_Base/Progress_Base.cpp \
    device/service/serviceDevicesAbstract.cpp \
    device/Progress_TMK24/Progress_tmk24Service.cpp \
    device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018_Data.cpp \
    device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.cpp \
    device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.cpp \
    database/database.cpp \
    update/updater.cpp \
    translate/qmltranslator.cpp \
    device/deviceCollector.cpp \
    device/deviceController.cpp \
    connection/connection.cpp \
    view/controller.cpp \
    view/peripherals.cpp \
    view/session.cpp \
    session/sessionProperty.cpp \
    session/sessionSecurity.cpp \
    view/module/modelDevTree.cpp

RESOURCES += \
    qml.qrc \
    images.qrc \
    font.qrc \
    database/db.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    connection/connectionFactory.h \
    device/deviceAbstract.h \
    device/devicesFactory.h \
    interfaces/interfaceAbstract.h \
    interfaces/interfaceSerial.h \
    command/commandController.h \
    other/crc.h \
    tests/testDevReply.h \
    view/module/treeitem.h \
    view/module/radialbar.h \
    device/Progress_TMK24/Progress_tmk24Data.h \
    device/Progress_TMK24/Progress_tmk24.h \
    device/Progress_TMK4UX/Progress_tmk4UXData.h \
    device/Progress_TMK4UX/Progress_tmk4UX.h \
    device/Progress_Base/Progress_Base_Data.h \
    device/Progress_Base/Progress_BaseData.h \
    device/Progress_Base/Progress_Base.h \
    device/service/serviceDevicesAbstract.h \
    device/Progress_TMK24/Progress_tmk24Service.h \
    device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018_Data.h \
    device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h \
    device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.h \
    database/database.h \
    update/updater.h \
    translate/qmltranslator.h \
    device/deviceCollector.h \
    device/deviceController.h \
    connection/connection.h \
    view/controller.h \
    view/peripherals.h \
    view/session.h \
    session/sessionProperty.h \
    session/sessionSecurity.h \
    interfaces/interfacesAbstract.h \
    view/module/modelDevTree.h

DISTFILES += device/service/serviceDevicesAbstract
