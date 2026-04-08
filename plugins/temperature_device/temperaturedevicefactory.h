#pragma once

#include <QObject>

#include "imodbusdevicefactory.h"

class TemperatureDeviceFactory : public QObject, public IModbusDeviceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ModbusDeviceFactory_iid FILE "temperature_device.json")
    Q_INTERFACES(IModbusDeviceFactory)

public:
    QString pluginName() const override;
    QStringList supportedDeviceTypes() const override;
    ModbusDeviceBase* createDevice(const QString& deviceType,
                                   QObject* parent = nullptr) override;
};
