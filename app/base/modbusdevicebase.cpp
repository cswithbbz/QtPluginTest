#include "modbusdevicebase.h"

ModbusDeviceBase::ModbusDeviceBase(const QString& deviceType, QObject* parent)
    : QObject(parent)
    , m_deviceType(deviceType)
{
}

void ModbusDeviceBase::setDeviceName(const QString& name)
{
    m_deviceName = name;
}

QString ModbusDeviceBase::deviceName() const
{
    return m_deviceName;
}

void ModbusDeviceBase::setSlaveAddress(int address)
{
    m_slaveAddress = address;
}

int ModbusDeviceBase::slaveAddress() const
{
    return m_slaveAddress;
}

QString ModbusDeviceBase::deviceType() const
{
    return m_deviceType;
}

bool ModbusDeviceBase::start()
{
    m_running = true;
    log(QStringLiteral("device started"));
    return m_running;
}

void ModbusDeviceBase::stop()
{
    if (!m_running) {
        return;
    }

    m_running = false;
    log(QStringLiteral("device stopped"));
}

void ModbusDeviceBase::log(const QString& message)
{
    emit logMessage(QStringLiteral("[%1] %2").arg(m_deviceType, message));
}
