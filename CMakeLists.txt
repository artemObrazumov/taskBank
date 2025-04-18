cmake_minimum_required(VERSION 3.14)

project(taskBank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/win")

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Svg)
find_package(SQLite3 REQUIRED)
qt_standard_project_setup()

set(RESOURCE_FILES
    resources.qrc
)
qt_add_resources(RESOURCES "resources" ${RESOURCE_FILES})
add_executable(taskBank main.cpp ${RESOURCES})

qt_add_qml_module(taskBank
    URI path
    VERSION 1.0
    QML_FILES main.qml
    SOURCES common/database.h common/database.cpp
    SOURCES repositories/ControlWorksRepository.h repositories/ControlWorksRepository.cpp
    SOURCES models/controlwork.h
    SOURCES component/controlworkscomponent.h component/controlworkscomponent.cpp
    QML_FILES qml/Container.qml qml/AddProjectWindow.qml
    RESOURCES resources.qrc
)

target_link_libraries(taskBank
    PRIVATE Qt6::Quick Qt6::Svg
)
target_link_libraries(taskBank
    PRIVATE SQLite::SQLite3
)

include(GNUInstallDirs)
install(TARGETS taskBank
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
