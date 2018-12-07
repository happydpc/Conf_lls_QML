#include "session.h"

Session::Session(QObject *parent) : QObject(parent)
{
    this->sessionSecurity = new SessionSecurity();
}

void Session::resetSession() {
//    disconnect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
//    disconnectToDevSignals();
//    for(int devCout=0;devCout<connFactory->getCountConnection(); devCout++) {
//        getDeviceFactoryByIndex(devCout)->removeDeviceAll();
//    }
//    connFactory->removeAll();
//    interfaceTree->removeAll();
//    connectToDevSignals();
//    connect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
//    emit interfaceAndDeviceListIsEmpty();
//    emit clearAllFrontEndItems();
}

bool Session::removeSessionByName(std::string sessionName) {
    return sessionSecurity->removeSession(sessionName);
}

std::list<std::string> Session::getListSession() {
    return sessionSecurity->getAvailableSessions();
}

bool Session::loadSession(std::string sessionName) {
//    Session t_load_session = sessionSecurity->getSessionByName(sessionName);
//    if(t_load_session.getIsValid()) {
//        for(auto itInteface:t_load_session.getInterfaces()) {
//            if(addConnection(itInteface.typeName, itInteface.name, itInteface.propKey, itInteface.propValue)) {
//                for(auto itDevice:itInteface.devices) {
//                    addDeviceToConnection(itInteface.name, itDevice.typeName, itDevice.propKey, itDevice.propValue);
//                }
//                emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
//                                                getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
//            }
//        }
//    }
//    return t_load_session.getIsValid();
}

std::string Session::saveCurrentSession() {
//    Session session;
//    Session::sDevices t_session_dev;
//    Session::sInterface t_session_io;
//    int connAll = connFactory->getCountConnection();
//    session.setSessionName("Сеанс_" + QDateTime::currentDateTimeUtc().toString("yyyy/M/d/hh:mm:ss:z"));
//    for(int ioCounter=0; ioCounter<connAll; ioCounter++) {
//        DevicesFactory *p_dev_factory = nullptr;
//        // interfaces
//        t_session_io.name = connFactory->getInterace(ioCounter)->getInterfaceName();
//        t_session_io.propKey = connFactory->getInterace(ioCounter)->getInterfaceProperty().first;
//        t_session_io.propValue = connFactory->getInterace(ioCounter)->getInterfaceProperty().second;
//        t_session_io.typeName= connFactory->getInterace(ioCounter)->getType();
//        session.addInterface(t_session_io);
//        // devices
//        p_dev_factory = connFactory->getDeviceController(ioCounter)->getDeviceFactory();
//        if(p_dev_factory != nullptr) {
//            int devAll = p_dev_factory->getDeviceCount();
//            for(int devCounter=0; devCounter<devAll; devCounter++) {
//                t_session_dev.propKey.clear();
//                t_session_dev.propValue.clear();
//                t_session_dev.typeName = p_dev_factory->getDeviceName(devCounter);
//                t_session_dev.propKey = p_dev_factory->getDevicePropertyByIndex(devCounter).first;
//                t_session_dev.propValue = p_dev_factory->getDevicePropertyByIndex(devCounter).second;
//                session.addDevice(t_session_dev);
//            }
//        }
//    }
//    std::string resNameSession = sessionSecurity->saveSession(session);
//    return resNameSession;
}

std::string Session::saveCurrentSessionAs(std::string sessionName) {
//    Session session;
//    Session::sDevices t_session_dev;
//    Session::sInterface t_session_io;
//    int connAll = connFactory->getCountConnection();
//    session.setSessionName(std::string("%1_%2").arg(sessionName).arg(QDateTime::currentDateTimeUtc().toString("yyyy/M/d/hh:mm:ss:z")));
//    for(int ioCounter=0; ioCounter<connAll; ioCounter++) {
//        DevicesFactory *p_dev_factory = nullptr;
//        // interfaces
//        t_session_io.name = connFactory->getInterace(ioCounter)->getInterfaceName();
//        t_session_io.propKey = connFactory->getInterace(ioCounter)->getInterfaceProperty().first;
//        t_session_io.propValue = connFactory->getInterace(ioCounter)->getInterfaceProperty().second;
//        t_session_io.typeName= connFactory->getInterace(ioCounter)->getType();
//        session.addInterface(t_session_io);
//        // devices
//        p_dev_factory = connFactory->getDeviceController(ioCounter)->getDeviceFactory();
//        if(p_dev_factory != nullptr) {
//            int devAll = p_dev_factory->getDeviceCount();
//            for(int devCounter=0; devCounter<devAll; devCounter++) {
//                t_session_dev.propKey.clear();
//                t_session_dev.propValue.clear();
//                t_session_dev.typeName = p_dev_factory->getDeviceName(devCounter);
//                t_session_dev.propKey = p_dev_factory->getDevicePropertyByIndex(devCounter).first;
//                t_session_dev.propValue = p_dev_factory->getDevicePropertyByIndex(devCounter).second;
//                session.addDevice(t_session_dev);
//            }
//        }
//    }
//    std::string resNameSession = sessionSecurity->saveSession(session);
//    return resNameSession;
}
