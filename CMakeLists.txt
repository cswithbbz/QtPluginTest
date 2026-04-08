cmake_minimum_required(VERSION 3.16)

project(QtPluginTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(app)
add_subdirectory(plugins)
