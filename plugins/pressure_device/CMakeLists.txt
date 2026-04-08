find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_plugin(pressure_device
    CLASS_NAME PressureDeviceFactory
    pressuredevice.cpp
    pressuredevicefactory.cpp
)

target_include_directories(pressure_device PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pressure_device PRIVATE
    Qt6::Core
    app_device_api
)

set_target_properties(pressure_device PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app/plugins
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app/plugins
)
