#pragma once

#include <QtPlugin>
#include <QString>
#include <QStringList>

class QObject;
class ModbusDeviceBase;

class IModbusDeviceFactory
{
public:
    virtual ~IModbusDeviceFactory() = default;

    virtual QString pluginName() const = 0;
    virtual QStringList supportedDeviceTypes() const = 0;
    virtual ModbusDeviceBase* createDevice(const QString& deviceType,
                                           QObject* parent = nullptr) = 0;
};

#define ModbusDeviceFactory_iid "com.example.QtPluginTest.IModbusDeviceFactory"
Q_DECLARE_INTERFACE(IModbusDeviceFactory, ModbusDeviceFactory_iid)
