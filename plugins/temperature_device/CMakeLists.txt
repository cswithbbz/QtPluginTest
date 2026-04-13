find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(temperature_device MODULE
    temperaturedevice.cpp
    temperaturedevicefactory.cpp
    temperaturedevice.h
    temperaturedevicefactory.h
)

target_include_directories(temperature_device PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(temperature_device PRIVATE
    Qt5::Core
    app_device_api
)

set_target_properties(temperature_device PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app/plugins
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app/plugins
)
