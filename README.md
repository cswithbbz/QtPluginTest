# Qt Plugin Test - Modbus Device Plugin Example

这是一个最小化的 Qt5 插件示例项目，用于验证 Modbus 风格设备的插件加载和数据收集机制。

## 项目概述

本项目演示了如何在 Qt 应用中使用插件架构实现模块化设备管理。每个设备类型（如温度传感器、压力传感器）都实现为独立的插件，通过共享接口与主应用通信。

## 项目结构

```
.
├── app/                          # 主应用和共享 API
│   ├── main.cpp                 # 应用入口
│   ├── mainwindow.cpp/h         # 主窗口
│   ├── plugintest.ui            # UI 定义
│   ├── interfaces/              # 共享接口头文件
│   │   ├── imodbusdevicefactory.h      # 设备工厂接口
│   │   ├── modbusdevicebase.h          # 设备基类
│   │   └── devicetypes.h               # 设备类型常量
│   ├── base/                    # 共享基类实现
│   │   └── modbusdevicebase.cpp
│   └── CMakeLists.txt
├── plugins/                      # 插件集合
│   ├── temperature_device/      # 温度设备插件
│   │   ├── temperaturedevice.h/cpp
│   │   ├── temperaturedevicefactory.h/cpp
│   │   ├── temperature_device.json     # 插件元数据
│   │   └── CMakeLists.txt
│   ├── pressure_device/         # 压力设备插件
│   │   ├── pressuredevice.h/cpp
│   │   ├── pressuredevicefactory.h/cpp
│   │   ├── pressure_device.json        # 插件元数据
│   │   └── CMakeLists.txt
│   └── CMakeLists.txt
├── build/                        # 构建输出目录（勿提交）
├── CMakeLists.txt               # 顶级 CMake 配置
└── README.md
```

## 前置要求

- **CMake** 3.16 或更高版本
- **Qt5** 5.12 或更高版本，安装位置已配置
- **C++17** 兼容编译器（GCC、Clang 或 MSVC）

## 构建步骤

### 1. 配置项目

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/5.x.x/gcc_64
```

**注意**：根据你的 Qt 安装路径调整 `CMAKE_PREFIX_PATH`。常见路径示例：
- Linux: `/opt/Qt/5.15.2/gcc_64`
- macOS: `/Users/username/Qt/5.15.2/clang_64`

如果 Qt5 不可被发现，也可以设置 `Qt5_DIR` 变量：
```bash
cmake -S . -B build -DQt5_DIR=/path/to/Qt/5.x.x/gcc_64/lib/cmake/Qt5
```

### 2. 构建应用和插件

```bash
cmake --build build
```

### 3. 运行应用

```bash
./build/app/plugin_demo
```

应用会自动从 `build/app/plugins/` 目录加载所有插件。

## 使用说明

1. 启动应用后，主窗口会显示已加载的设备列表
2. 每个插件提供虚拟数据（模拟真实传感器数据）
3. 应用通过 `IModbusDeviceFactory` 接口动态发现和加载插件
4. 设备数据通过 `ModbusDeviceBase::collectData()` 方法获取

## 添加新设备

要添加新的设备类型，请按以下步骤操作：

1. 在 `plugins/` 下创建新目录，例如 `plugins/humidity_device/`
2. 创建以下文件：
   - `humiditydevice.h` / `humiditydevice.cpp` - 继承 `ModbusDeviceBase`
   - `humiditydevicefactory.h` / `humiditydevicefactory.cpp` - 继承 `IModbusDeviceFactory`
   - `humidity_device.json` - 插件元数据
   - `CMakeLists.txt` - 构建配置
3. 在 `CMakeLists.txt` 中遵循现有插件的模式
4. 确保工厂类通过 `Q_PLUGIN_METADATA` 宏正确声明

详见 [AGENTS.md](AGENTS.md) 中的架构说明。

## 开发规范

### 命名约定
- 类名：`PascalCase`（例：`TemperatureDeviceFactory`）
- 文件名：小写（例：`temperaturedevice.h`）
- Qt 类型优先：使用 `QString`、`QList` 等 Qt 容器

### 代码风格
- 缩进：4 个空格
- 类和函数定义的花括号另起一行

```cpp
class MyClass
{
    // class body
};

void myFunction()
{
    // function body
}
```

### 优先使用 Qt 字符串字面量
```cpp
// 推荐
const auto path = QStringLiteral("path/to/file");

// 不推荐
const auto path = "path/to/file";
```

## 验证和测试

目前没有自动化测试框架。请通过以下方式验证更改：

1. ✓ 成功编译（无编译错误）
2. ✓ 运行 `./build/app/plugin_demo`
3. ✓ 确认所有插件正确加载
4. ✓ 验证每个插件返回预期的虚拟数据

## 架构设计

```
┌─────────────────────┐
│   主应用 (app)       │
│  ┌───────────────┐  │
│  │ PluginLoader  │  │
│  └───────────────┘  │
└──────────┬──────────┘
           │
     ┌─────┴──────┬──────────┬──────────┐
     │            │          │          │
┌────▼───┐  ┌────▼───┐ ┌───▼────┐ ...
│ 温度   │  │ 压力   │ │ 湿度   │
│插件    │  │插件    │ │插件    │
└────────┘  └────────┘ └────────┘
```

- **共享接口**（`app/interfaces/`）：所有插件和主应用都依赖
- **设备基类**（`ModbusDeviceBase`）：提供通用功能
- **工厂模式**（`IModbusDeviceFactory`）：主应用通过此接口发现和创建设备实例

## 故障排除

### Qt5 找不到
**问题**：CMake 配置失败，提示 "Could not find Qt5"

**解决方案**：
```bash
# 查找 Qt 安装路径
find ~ -name "Qt5Config.cmake" 2>/dev/null

# 使用正确的路径配置
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/qt
```

### 插件无法加载
**问题**：运行应用时插件不被识别

**排查步骤**：
1. 检查 `build/app/plugins/` 目录是否包含 `.so`（Linux）或 `.dll`（Windows）文件
2. 验证 JSON 元数据文件有效（JSON 格式是否正确）
3. 确保插件在 `IModbusDeviceFactory` 接口上正确注册

## 许可证

[如适用，添加许可证信息]

## 贡献

提交拉取请求时，请确保：
- 代码遵循项目风格指南
- 新插件成功编译和加载
- 提供简要的更改说明和示例输出

---

**最后更新**：2026 年 4 月
