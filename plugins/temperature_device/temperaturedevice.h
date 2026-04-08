#pragma once

#include "modbusdevicebase.h"

class TemperatureDevice : public ModbusDeviceBase
{
    Q_OBJECT

public:
    explicit TemperatureDevice(QObject* parent = nullptr);

    QVariantMap collectData() override;
};
