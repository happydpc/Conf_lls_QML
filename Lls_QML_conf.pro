QT += quick
QT += serialport
QT += charts qml
QT += sql
CONFIG += c++14

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
    connection/connectionFactory.cpp \
    device/deviceAbstract.cpp \
    device/devicesFactory.cpp \
    interfaces/interfaceBLE.cpp \
    interfaces/interfaceEthernet.cpp \
    interfaces/interfacesAbstract.cpp \
    interfaces/interfaceSerial.cpp \
    settings/settings.cpp \
    view/viewController.cpp \
    command/commandController.cpp \
    other/crc.cpp \
    tests/testDevReply.cpp \
    view/interfaceListControll/treeitem.cpp \
    view/interfaceListControll/model.cpp \
    view/radialbar.cpp \
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
    database/database.cpp

RESOURCES += \
    qml.qrc \
    images.qrc \
    font.qrc

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
    interfaces/interfaceBLE.h \
    interfaces/interfaceEthernet.h \
    interfaces/interfacesAbstract.h \
    interfaces/interfaceSerial.h \
    settings/settings.h \
    view/viewController.h \
    command/commandController.h \
    other/crc.h \
    tests/testDevReply.h \
    view/interfaceListControll/model.h \
    view/interfaceListControll/treeitem.h \
    view/radialbar.h \
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
    database/database.h

DISTFILES += \
    device/service/serviceDevicesAbstract
    icon.rc

RC_FILE += icon.rc
