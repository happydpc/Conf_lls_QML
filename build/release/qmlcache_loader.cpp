#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,1,0,0,0,1,0,0,0,
8,0,2,0,0,0,7,0,0,0,2,0,0,3,194,0,
2,0,0,0,7,0,0,0,30,0,0,0,20,0,0,0,
0,0,1,0,0,0,0,0,0,4,218,0,2,0,0,0,
4,0,0,0,26,0,0,0,220,0,2,0,0,0,6,0,
0,0,20,0,0,1,224,0,2,0,0,0,8,0,0,0,
12,0,0,0,62,0,2,0,0,0,3,0,0,0,9,0,
0,0,40,0,0,0,0,0,1,0,0,0,0,0,0,0,
124,0,0,0,0,0,1,0,0,0,0,0,0,0,88,0,
0,0,0,0,1,0,0,0,0,0,0,0,180,0,0,0,
0,0,1,0,0,0,0,0,0,2,52,0,0,0,0,0,
1,0,0,0,0,0,0,2,168,0,0,0,0,0,1,0,
0,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,
0,0,0,3,100,0,0,0,0,0,1,0,0,0,0,0,
0,1,244,0,0,0,0,0,1,0,0,0,0,0,0,2,
212,0,0,0,0,0,1,0,0,0,0,0,0,2,106,0,
0,0,0,0,1,0,0,0,0,0,0,3,62,0,0,0,
0,0,1,0,0,0,0,0,0,1,138,0,0,0,0,0,
1,0,0,0,0,0,0,0,240,0,0,0,0,0,1,0,
0,0,0,0,0,1,186,0,0,0,0,0,1,0,0,0,
0,0,0,1,104,0,0,0,0,0,1,0,0,0,0,0,
0,1,60,0,0,0,0,0,1,0,0,0,0,0,0,1,
18,0,0,0,0,0,1,0,0,0,0,0,0,5,48,0,
0,0,0,0,1,0,0,0,0,0,0,4,242,0,0,0,
0,0,1,0,0,0,0,0,0,5,12,0,0,0,0,0,
1,0,0,0,0,0,0,5,98,0,0,0,0,0,1,0,
0,0,0,0,0,4,32,0,0,0,0,0,1,0,0,0,
0,0,0,4,186,0,0,0,0,0,1,0,0,0,0,0,
0,4,110,0,0,0,0,0,1,0,0,0,0,0,0,4,
4,0,0,0,0,0,1,0,0,0,0,0,0,3,224,0,
0,0,0,0,1,0,0,0,0,0,0,4,60,0,0,0,
0,0,1,0,0,0,0,0,0,4,156,0,0,0,0,0,
1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,3,0,0,120,60,0,113,0,
109,0,108,0,7,8,115,88,252,0,97,0,112,0,112,0,
46,0,113,0,109,0,108,0,8,15,202,95,188,0,86,0,
105,0,101,0,119,0,46,0,113,0,109,0,108,0,10,12,
130,114,131,0,105,0,110,0,116,0,101,0,114,0,102,0,
97,0,99,0,101,0,115,0,15,10,72,174,60,0,77,0,
101,0,115,0,115,0,97,0,103,0,101,0,83,0,104,0,
111,0,119,0,46,0,113,0,109,0,108,0,25,2,243,99,
60,0,68,0,101,0,118,0,80,0,114,0,111,0,112,0,
101,0,114,0,116,0,121,0,83,0,101,0,114,0,105,0,
97,0,108,0,80,0,111,0,114,0,116,0,46,0,113,0,
109,0,108,0,17,14,151,244,188,0,65,0,100,0,100,0,
83,0,101,0,114,0,105,0,97,0,108,0,80,0,111,0,
114,0,116,0,46,0,113,0,109,0,108,0,7,10,203,184,
117,0,100,0,101,0,118,0,84,0,114,0,101,0,101,0,
14,1,43,115,252,0,68,0,101,0,118,0,105,0,99,0,
101,0,84,0,114,0,101,0,101,0,46,0,113,0,109,0,
108,0,18,15,71,66,60,0,69,0,100,0,105,0,116,0,
68,0,101,0,118,0,105,0,99,0,101,0,78,0,97,0,
109,0,101,0,46,0,113,0,109,0,108,0,19,13,211,132,
124,0,68,0,101,0,118,0,105,0,99,0,101,0,73,0,
116,0,101,0,109,0,69,0,109,0,112,0,116,0,121,0,
46,0,113,0,109,0,108,0,14,3,35,114,156,0,68,0,
101,0,118,0,105,0,99,0,101,0,73,0,116,0,101,0,
109,0,46,0,113,0,109,0,108,0,21,0,255,81,28,0,
73,0,110,0,116,0,101,0,114,0,102,0,97,0,99,0,
101,0,73,0,116,0,101,0,109,0,86,0,105,0,101,0,
119,0,46,0,113,0,109,0,108,0,16,2,184,202,124,0,
68,0,101,0,118,0,76,0,105,0,115,0,116,0,80,0,
97,0,110,0,101,0,108,0,46,0,113,0,109,0,108,0,
7,10,204,249,3,0,100,0,101,0,118,0,105,0,99,0,
101,0,115,0,29,4,229,179,188,0,68,0,101,0,118,0,
80,0,114,0,111,0,112,0,101,0,114,0,116,0,121,0,
80,0,114,0,111,0,103,0,114,0,101,0,115,0,115,0,
84,0,109,0,107,0,52,0,117,0,120,0,46,0,113,0,
109,0,108,0,24,1,105,247,60,0,65,0,100,0,100,0,
68,0,101,0,118,0,105,0,99,0,101,0,84,0,97,0,
114,0,105,0,114,0,68,0,105,0,97,0,108,0,111,0,
103,0,46,0,113,0,109,0,108,0,28,12,165,186,92,0,
68,0,101,0,118,0,80,0,114,0,111,0,112,0,101,0,
114,0,116,0,121,0,80,0,114,0,111,0,103,0,114,0,
101,0,115,0,115,0,84,0,109,0,107,0,50,0,52,0,
46,0,113,0,109,0,108,0,19,2,203,168,60,0,65,0,
100,0,100,0,68,0,101,0,118,0,105,0,99,0,101,0,
68,0,105,0,97,0,108,0,111,0,103,0,46,0,113,0,
109,0,108,0,19,6,4,146,156,0,67,0,104,0,97,0,
110,0,103,0,101,0,68,0,101,0,118,0,73,0,100,0,
78,0,97,0,109,0,101,0,46,0,113,0,109,0,108,0,
28,3,50,39,156,0,68,0,101,0,118,0,80,0,114,0,
111,0,112,0,101,0,114,0,116,0,121,0,78,0,111,0,
122,0,122,0,108,0,101,0,95,0,118,0,95,0,48,0,
95,0,48,0,48,0,46,0,113,0,109,0,108,0,16,14,
187,99,156,0,83,0,101,0,97,0,114,0,99,0,104,0,
68,0,101,0,118,0,105,0,99,0,101,0,46,0,113,0,
109,0,108,0,44,3,252,193,28,0,68,0,101,0,118,0,
80,0,114,0,111,0,112,0,101,0,114,0,116,0,121,0,
80,0,114,0,111,0,103,0,114,0,101,0,115,0,115,0,
84,0,109,0,107,0,50,0,52,0,84,0,97,0,114,0,
84,0,97,0,98,0,108,0,101,0,68,0,101,0,108,0,
101,0,103,0,97,0,116,0,101,0,46,0,113,0,109,0,
108,0,12,4,100,197,220,0,112,0,114,0,111,0,106,0,
101,0,99,0,116,0,80,0,97,0,110,0,101,0,108,0,
15,8,227,21,28,0,77,0,97,0,105,0,110,0,77,0,
101,0,110,0,117,0,66,0,97,0,114,0,46,0,113,0,
109,0,108,0,11,6,34,218,220,0,83,0,117,0,112,0,
112,0,111,0,114,0,116,0,46,0,113,0,109,0,108,0,
11,1,18,197,124,0,83,0,101,0,115,0,115,0,105,0,
111,0,110,0,46,0,113,0,109,0,108,0,22,15,141,253,
28,0,80,0,114,0,111,0,106,0,101,0,99,0,116,0,
68,0,101,0,118,0,105,0,99,0,101,0,80,0,97,0,
110,0,101,0,108,0,46,0,113,0,109,0,108,0,20,4,
32,228,252,0,80,0,114,0,111,0,106,0,101,0,99,0,
116,0,77,0,97,0,105,0,110,0,83,0,116,0,97,0,
99,0,107,0,46,0,113,0,109,0,108,0,12,15,223,34,
60,0,83,0,101,0,116,0,116,0,105,0,110,0,103,0,
115,0,46,0,113,0,109,0,108,0,13,2,3,221,252,0,
76,0,111,0,103,0,111,0,80,0,97,0,110,0,101,0,
108,0,46,0,113,0,109,0,108,0,9,9,124,196,67,0,
109,0,105,0,115,0,99,0,69,0,108,0,101,0,109,0,
115,0,10,11,104,113,92,0,66,0,117,0,116,0,116,0,
111,0,110,0,46,0,113,0,109,0,108,0,15,14,251,75,
188,0,84,0,97,0,98,0,66,0,117,0,116,0,116,0,
111,0,110,0,85,0,112,0,46,0,113,0,109,0,108,0,
22,0,169,167,28,0,65,0,110,0,105,0,109,0,97,0,
116,0,101,0,100,0,65,0,114,0,101,0,97,0,83,0,
101,0,114,0,105,0,101,0,115,0,46,0,113,0,109,0,
108,0,15,15,42,5,220,0,66,0,117,0,116,0,116,0,
111,0,110,0,82,0,111,0,117,0,110,0,100,0,46,0,
113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _qml_miscElems_ButtonRound_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_LogoPanel_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_Settings_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_miscElems_AnimatedAreaSeries_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_DevPropertyProgressTmk24TarTableDelegate_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_SearchDevice_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_ProjectMainStack_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devTree_DevListPanel_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_ProjectDevicePanel_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_interfaces_AddSerialPort_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devTree_InterfaceItemView_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_miscElems_TabButtonUp_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_DevPropertyNozzle_v_0_00_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devTree_DeviceItem_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_ChangeDevIdName_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devTree_DeviceItemEmpty_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_AddDeviceDialog_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_interfaces_DevPropertySerialPort_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_Session_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_DevPropertyProgressTmk24_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_interfaces_MessageShow_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devTree_EditDeviceName_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_Support_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_View_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devTree_DeviceTree_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_projectPanel_MainMenuBar_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_AddDeviceTarirDialog_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_app_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_miscElems_Button_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_devices_DevPropertyProgressTmk4ux_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry);


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/miscElems/ButtonRound.qml"), &QmlCacheGeneratedCode::_qml_miscElems_ButtonRound_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/LogoPanel.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_LogoPanel_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/Settings.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_Settings_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/miscElems/AnimatedAreaSeries.qml"), &QmlCacheGeneratedCode::_qml_miscElems_AnimatedAreaSeries_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/DevPropertyProgressTmk24TarTableDelegate.qml"), &QmlCacheGeneratedCode::_qml_devices_DevPropertyProgressTmk24TarTableDelegate_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/SearchDevice.qml"), &QmlCacheGeneratedCode::_qml_devices_SearchDevice_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/ProjectMainStack.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_ProjectMainStack_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devTree/DevListPanel.qml"), &QmlCacheGeneratedCode::_qml_devTree_DevListPanel_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/ProjectDevicePanel.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_ProjectDevicePanel_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/interfaces/AddSerialPort.qml"), &QmlCacheGeneratedCode::_qml_interfaces_AddSerialPort_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devTree/InterfaceItemView.qml"), &QmlCacheGeneratedCode::_qml_devTree_InterfaceItemView_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/miscElems/TabButtonUp.qml"), &QmlCacheGeneratedCode::_qml_miscElems_TabButtonUp_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/DevPropertyNozzle_v_0_00.qml"), &QmlCacheGeneratedCode::_qml_devices_DevPropertyNozzle_v_0_00_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devTree/DeviceItem.qml"), &QmlCacheGeneratedCode::_qml_devTree_DeviceItem_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/ChangeDevIdName.qml"), &QmlCacheGeneratedCode::_qml_devices_ChangeDevIdName_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devTree/DeviceItemEmpty.qml"), &QmlCacheGeneratedCode::_qml_devTree_DeviceItemEmpty_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/AddDeviceDialog.qml"), &QmlCacheGeneratedCode::_qml_devices_AddDeviceDialog_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/interfaces/DevPropertySerialPort.qml"), &QmlCacheGeneratedCode::_qml_interfaces_DevPropertySerialPort_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/Session.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_Session_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/DevPropertyProgressTmk24.qml"), &QmlCacheGeneratedCode::_qml_devices_DevPropertyProgressTmk24_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/interfaces/MessageShow.qml"), &QmlCacheGeneratedCode::_qml_interfaces_MessageShow_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devTree/EditDeviceName.qml"), &QmlCacheGeneratedCode::_qml_devTree_EditDeviceName_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/Support.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_Support_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/View.qml"), &QmlCacheGeneratedCode::_qml_View_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devTree/DeviceTree.qml"), &QmlCacheGeneratedCode::_qml_devTree_DeviceTree_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/projectPanel/MainMenuBar.qml"), &QmlCacheGeneratedCode::_qml_projectPanel_MainMenuBar_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/AddDeviceTarirDialog.qml"), &QmlCacheGeneratedCode::_qml_devices_AddDeviceTarirDialog_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/app.qml"), &QmlCacheGeneratedCode::_qml_app_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/miscElems/Button.qml"), &QmlCacheGeneratedCode::_qml_miscElems_Button_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/devices/DevPropertyProgressTmk4ux.qml"), &QmlCacheGeneratedCode::_qml_devices_DevPropertyProgressTmk4ux_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}
const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml));
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    return 1;
}
