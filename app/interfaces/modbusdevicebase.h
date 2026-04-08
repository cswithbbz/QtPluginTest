#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

class ModbusDeviceBase : public QObject
{
    Q_OBJECT

public:
    explicit ModbusDeviceBase(const QString& deviceType, QObject* parent = nullptr);
    ~ModbusDeviceBase() override = default;

    void setDeviceName(const QString& name);
    QString deviceName() const;

    void setSlaveAddress(int address);
    int slaveAddress() const;

    QString deviceType() const;

    virtual bool start();
    virtual void stop();
    virtual QVariantMap collectData() = 0;

signals:
    void logMessage(const QString& message);

protected:
    void log(const QString& message);

private:
    QString m_deviceType;
    QString m_deviceName;
    int m_slaveAddress = 1;
    bool m_running = false;
};
