find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(pressure_device MODULE
    pressuredevice.cpp
    pressuredevicefactory.cpp
    pressuredevice.h
    pressuredevicefactory.h
)

target_include_directories(pressure_device PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pressure_device PRIVATE
    Qt5::Core
    app_device_api
)

set_target_properties(pressure_device PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app/plugins
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/app/plugins
)
