#include "temperaturedevice.h"

#include "devicetypes.h"

TemperatureDevice::TemperatureDevice(QObject* parent)
    : ModbusDeviceBase(QString::fromLatin1(DeviceTypes::Temperature), parent)
{
}

QVariantMap TemperatureDevice::collectData()
{
    return {
        {QStringLiteral("deviceType"), deviceType()},
        {QStringLiteral("deviceName"), deviceName()},
        {QStringLiteral("address"), slaveAddress()},
        {QStringLiteral("value"), 26.4},
        {QStringLiteral("unit"), QStringLiteral("C")},
        {QStringLiteral("status"), QStringLiteral("ok")},
    };
}
