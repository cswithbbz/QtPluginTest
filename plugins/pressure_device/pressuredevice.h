#pragma once

#include "modbusdevicebase.h"

class PressureDevice : public ModbusDeviceBase
{
    Q_OBJECT

public:
    explicit PressureDevice(QObject* parent = nullptr);

    QVariantMap collectData() override;
};
