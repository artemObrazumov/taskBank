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
    SOURCES nlohmann/json.hpp
    SOURCES repositories/ControlWorksRepository.h repositories/ControlWorksRepository.cpp
    SOURCES models/controlwork.h
    SOURCES component/controlworkscomponent.h component/controlworkscomponent.cpp
    QML_FILES qml/Container.qml qml/AddProjectWindow.qml qml/ProjectEditorWindow.qml qml/ConfirmationWindow.qml qml/TabsRow.qml qml/TaskEditor.qml
        qml/TagsRow.qml qml/TagsWindow.qml qml/AddTagWindow.qml qml/GenerateVariantsWindow.qml qml/CheckboxList.qml
    RESOURCES resources.qrc
    SOURCES  repositories/controlworkeditorrepository.cpp
    SOURCES models/task.h
    SOURCES Constants.h
    SOURCES databases/controlworkdatabase.h databases/controlworkdatabase.cpp
    SOURCES utils/controlworkmetadataeditor.h utils/controlworkmetadataeditor.cpp
    SOURCES models/taskgroup.h
    SOURCES databases/controlworkcontentdatabase.h databases/controlworkcontentdatabase.cpp
    SOURCES component/controlworkeditorcomponent.h component/controlworkeditorcomponent.cpp
    SOURCES component/utils/TaskGroupsModel.h component/utils/TaskTabsModel.h component/utils/tasktagsmodel.h
    SOURCES models/Tag.h
    SOURCES
    SOURCES component/utils/AttachmentSaver.cpp
    SOURCES component/utils/AttachmentSaver.h
    SOURCES component/utils/CheckBoxListModel.h
    SOURCES utils/controlworkpdfexporter.h utils/controlworkpdfexporter.cpp
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
