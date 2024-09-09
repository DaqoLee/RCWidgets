#make_minimum_required(VERSION 3.16)
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(RCWidgets LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core )

find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        SerialPort
        Network
)
qt_standard_project_setup()

#set(RS21_sdk "C:/Users/26621/Desktop/RC/RCWidgets")


set(PROJECT_SOURCES
    main.cpp
    RCWidgets.ui
    RCWidgets.h
    RCWidgets.cpp
    RCMap.cpp
    RCMap.h
    Gauge.cpp
    Gauge.h
    SerialPort.cpp
    SerialPort.h
    ButtonBar.cpp
    ButtonBar.h

)


qt_add_executable(RCWidgets ${PROJECT_SOURCES})




#添加RS21_sdk头文件路径
target_include_directories(RCWidgets
    PUBLIC
     Qt${QT_VERSION_MAJOR}::Test
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


set_target_properties(RCWidgets
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(RCWidgets
    PUBLIC
      
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Network
        Qt6::SerialPort
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/MOZA_SDK.lib
)

add_test(
        NAME RCWidgets
        COMMAND $<TARGET_FILE:RCWidgets>
)
