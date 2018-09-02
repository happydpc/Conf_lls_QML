QT += quick
QT += serialport
CONFIG += c++17

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
    device/device.cpp \
    device/deviceAbstract.cpp \
    device/devicesFactory.cpp \
    interfaces/interfaceBLE.cpp \
    interfaces/interfaceEthernet.cpp \
    interfaces/interfacesAbstract.cpp \
    interfaces/interfaceSerial.cpp \
    settings/settings.cpp \
    view/viewController.cpp \
    interfaces/interface.cpp \
    command/commandController.cpp \
    device/subDevices/Progress_Base.cpp \
    device/subDevices/Progress_BaseData.cpp \
    device/subDevices/Progress_tmk13.cpp \
    device/subDevices/Progress_tmk13Data.cpp \
    device/subDevices/Progress_tmk24.cpp \
    device/subDevices/Progress_tmk24Data.cpp\
    other/crc.cpp \
    tests/testDevReply.cpp

RESOURCES += \
    qml.qrc

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
    device/device.h \
    device/deviceAbstract.h \
    device/devicesFactory.h \
    interfaces/interfaceBLE.h \
    interfaces/interfaceEthernet.h \
    interfaces/interfacesAbstract.h \
    interfaces/interfaceSerial.h \
    settings/settings.h \
    view/viewController.h \
    interfaces/interface.h \
    command/commandController.h \
    device/subDevices/Progress_Base.h \
    device/subDevices/Progress_BaseData.h \
    device/subDevices/Progress_tmk13.h \
    device/subDevices/Progress_tmk13Data.h \
    device/subDevices/Progress_tmk24.h \
    device/subDevices/Progress_tmk24Data.h\
    other/crc.h \
    tests/testDevReply.h

DISTFILES +=
