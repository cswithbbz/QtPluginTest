#include "pressuredevice.h"

#include "devicetypes.h"

PressureDevice::PressureDevice(QObject* parent)
    : ModbusDeviceBase(QString::fromLatin1(DeviceTypes::Pressure), parent)
{
}

QVariantMap PressureDevice::collectData()
{
    return {
        {QStringLiteral("deviceType"), deviceType()},
        {QStringLiteral("deviceName"), deviceName()},
        {QStringLiteral("address"), slaveAddress()},
        {QStringLiteral("value"), 101.3},
        {QStringLiteral("unit"), QStringLiteral("kPa")},
        {QStringLiteral("status"), QStringLiteral("ok")},
    };
}
