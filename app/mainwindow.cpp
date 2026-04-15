#include "mainwindow.h"
#include "ui_plugintest.h"
#include "imodbusdevicefactory.h"
#include "modbusdevicebase.h"

#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QJsonDocument>
#include <QDebug>

// 全局指针存储 TextBrowser
static QTextBrowser* g_outputBrowser = nullptr;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    if (!g_outputBrowser) {
        return;
    }

    QString typeStr;
    switch (type) {
        case QtDebugMsg:
            typeStr = QStringLiteral("[DEBUG]");
            break;
        case QtInfoMsg:
            typeStr = QStringLiteral("[INFO]");
            break;
        case QtWarningMsg:
            typeStr = QStringLiteral("[WARNING]");
            break;
        case QtCriticalMsg:
            typeStr = QStringLiteral("[ERROR]");
            break;
        case QtFatalMsg:
            typeStr = QStringLiteral("[FATAL]");
            break;
    }

    g_outputBrowser->append(typeStr + QStringLiteral(" ") + msg);
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    g_outputBrowser = ui->outputTextBrowser;

    // 安装消息处理器
    qInstallMessageHandler(messageHandler);

    // 连接按钮信号
    connect(ui->loadButton, &QPushButton::clicked,
            this, &MainWindow::onLoadPluginsClicked);
}

MainWindow::~MainWindow()
{
    qInstallMessageHandler(nullptr);
    delete ui;
}

void MainWindow::onLoadPluginsClicked()
{
    ui->outputTextBrowser->clear();
    qInfo() << QStringLiteral("=== Starting Plugin Load ===");

    const QDir pluginDir(QCoreApplication::applicationDirPath() + QStringLiteral("/plugins"));
    qInfo() << QStringLiteral("Plugin dir:") << pluginDir.absolutePath();

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
            qWarning() << QStringLiteral("Failed to load plugin:") << fileName
                      << loader.errorString();
            continue;
        }

        auto* factory = qobject_cast<IModbusDeviceFactory*>(pluginInstance);
        if (!factory) {
            qWarning() << QStringLiteral("Plugin does not implement IModbusDeviceFactory:")
                      << fileName;
            continue;
        }

        qInfo() << QStringLiteral("plugin:") << factory->pluginName();
        qInfo() << QStringLiteral("supported device types:")
               << factory->supportedDeviceTypes();

        for (const QString& deviceType : factory->supportedDeviceTypes()) {
            ModbusDeviceBase* device = factory->createDevice(deviceType, this);
            if (!device) {
                qWarning() << QStringLiteral("Failed to create device for type:")
                          << deviceType;
                continue;
            }

            device->setDeviceName(deviceType + QStringLiteral("_demo"));
            device->setSlaveAddress(deviceType == QStringLiteral("temperature") ? 1 : 2);
            device->start();

            const QVariantMap data = device->collectData();
            qInfo().noquote() << QJsonDocument::fromVariant(data).toJson(QJsonDocument::Compact);

            device->stop();
            device->deleteLater();
        }
    }

    qInfo() << QStringLiteral("=== Plugin Load Complete ===");
}
