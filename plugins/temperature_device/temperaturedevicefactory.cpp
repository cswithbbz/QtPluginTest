#include "temperaturedevicefactory.h"

#include "devicetypes.h"
#include "temperaturedevice.h"

QString TemperatureDeviceFactory::pluginName() const
{
    return QStringLiteral("Temperature Device Factory");
}

QStringList TemperatureDeviceFactory::supportedDeviceTypes() const
{
    return {QString::fromLatin1(DeviceTypes::Temperature)};
}

ModbusDeviceBase* TemperatureDeviceFactory::createDevice(const QString& deviceType, QObject* parent)
{
    if (deviceType == QLatin1String(DeviceTypes::Temperature)) {
        return new TemperatureDevice(parent);
    }

    return nullptr;
}
