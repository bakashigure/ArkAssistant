cmake_minimum_required(VERSION 3.1)

project(ArkAssistant)

set(APP_NAME "ArkAssistant")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)


find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

set(SOURCE
    ArkAssistant.qrc
    ArknightsAssistant.rc
    main.cpp
    StyleSheet.cpp
    AboutWindow.cpp
    ArkAssistant.cpp
    )


add_executable(${APP_NAME} WIN32 ${SOURCE})

target_link_libraries( ${APP_NAME}
Qt5::Widgets 
Qt5::Core 
Qt5::Gui)

INSTALL(TARGETS  ${APP_NAME}
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
)

 
