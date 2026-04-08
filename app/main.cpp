#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QLibrary>
#include <QPluginLoader>

#include "imodbusdevicefactory.h"
#include "modbusdevicebase.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    const QDir pluginDir(QCoreApplication::applicationDirPath() + "/plugins");
    qInfo() << "plugin dir:" << pluginDir.absolutePath();

    const QStringList filters = {
#if defined(Q_OS_WIN)
        QStringLiteral("*.dll")
#elif defined(Q_OS_MACOS)
        QStringLiteral("*.dylib")
#else
        QStringLiteral("*.so")
#endif
    };

    for (const QString& fileName : pluginDir.entryList(filters, QDir::Files)) {
        QPluginLoader loader(pluginDir.absoluteFilePath(fileName));
        QObject* pluginInstance = loader.instance();
        if (!pluginInstance) {
            qWarning() << "failed to load plugin:" << fileName << loader.errorString();
            continue;
        }

        auto* factory = qobject_cast<IModbusDeviceFactory*>(pluginInstance);
        if (!factory) {
            qWarning() << "plugin does not implement IModbusDeviceFactory:" << fileName;
            continue;
        }

        qInfo() << "plugin:" << factory->pluginName();
        qInfo() << "supported device types:" << factory->supportedDeviceTypes();

        for (const QString& deviceType : factory->supportedDeviceTypes()) {
            ModbusDeviceBase* device = factory->createDevice(deviceType, &app);
            if (!device) {
                qWarning() << "failed to create device for type:" << deviceType;
                continue;
            }

            device->setDeviceName(deviceType + QStringLiteral("_demo"));
            device->setSlaveAddress(deviceType == QStringLiteral("temperature") ? 1 : 2);
            device->start();

            const QVariantMap data = device->collectData();
            qInfo().noquote() << QJsonDocument::fromVariant(data).toJson(QJsonDocument::Compact);

            device->stop();
        }
    }

    return 0;
}
