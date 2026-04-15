find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

add_library(app_device_api STATIC
    base/modbusdevicebase.cpp
    interfaces/modbusdevicebase.h
)

target_include_directories(app_device_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
)

target_link_libraries(app_device_api PUBLIC Qt5::Core)

add_executable(plugin_demo
    main.cpp
    mainwindow.h
    mainwindow.cpp
    plugintest.ui
)

set_target_properties(plugin_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app
)

target_include_directories(plugin_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
)

target_link_libraries(plugin_demo PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    app_device_api
)
