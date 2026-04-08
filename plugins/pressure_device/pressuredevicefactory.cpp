#include "pressuredevicefactory.h"

#include "devicetypes.h"
#include "pressuredevice.h"

QString PressureDeviceFactory::pluginName() const
{
    return QStringLiteral("Pressure Device Factory");
}

QStringList PressureDeviceFactory::supportedDeviceTypes() const
{
    return {QString::fromLatin1(DeviceTypes::Pressure)};
}

ModbusDeviceBase* PressureDeviceFactory::createDevice(const QString& deviceType, QObject* parent)
{
    if (deviceType == QLatin1String(DeviceTypes::Pressure)) {
        return new PressureDevice(parent);
    }

    return nullptr;
}
