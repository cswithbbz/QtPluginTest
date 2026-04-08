# Repository Guidelines

## Project Structure & Module Organization
This repository is a minimal Qt plugin example for mock Modbus-style devices.

- `app/`: host application and shared API surface.
- `app/interfaces/`: shared headers used by the app and plugins, including `ModbusDeviceBase`, `IModbusDeviceFactory`, and device type constants.
- `app/base/`: shared base-class implementation.
- `plugins/`: one plugin per device.
- `plugins/temperature_device/`: temperature device plugin and metadata.
- `plugins/pressure_device/`: pressure device plugin and metadata.
- `build/`: local build output. Do not commit generated files.

When adding a new device, create a new directory under `plugins/` with its own `CMakeLists.txt`, device class, factory class, and JSON metadata file.

## Build, Test, and Development Commands
- `cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64`: configure the project.
- `cmake --build build`: build the app and plugins.
- `./build/app/plugin_demo`: run the host app and load plugins from `build/app/plugins`.

If Qt 6 is not discoverable, set `CMAKE_PREFIX_PATH` or `Qt6_DIR` to the correct Qt installation.

## Coding Style & Naming Conventions
- Use C++17 and Qt 6 APIs.
- Use 4-space indentation and keep braces on their own lines for class and function definitions.
- Class names use `PascalCase`, for example `TemperatureDeviceFactory`.
- File names follow the current pattern: `temperaturedevice.h`, `temperaturedevicefactory.cpp`.
- Prefer `QStringLiteral`, `QLatin1String`, and Qt container/value types where already used.
- Keep plugin interfaces in `app/interfaces/`; do not duplicate shared contracts inside plugins.

## Testing Guidelines
There is no automated test target yet. For now, validate changes by:

- Building successfully with CMake.
- Running `./build/app/plugin_demo`.
- Confirming each plugin loads and returns mock data.

If tests are added later, place them in a dedicated `tests/` directory and name files after the unit under test, such as `test_temperaturedevice.cpp`.

## Commit & Pull Request Guidelines
Git history is not available in this workspace, so use these conventions consistently:

- Write short, imperative commit messages, for example `Add humidity device plugin`.
- Keep each commit focused on one change.
- In pull requests, include a brief summary, affected paths, build/run steps, and sample output if plugin behavior changes.

## Architecture Notes
The host app owns plugin discovery. Each plugin exposes exactly one factory via `Q_PLUGIN_METADATA` and `IModbusDeviceFactory`, while concrete device classes inherit `ModbusDeviceBase` and return mock data through `collectData()`.
