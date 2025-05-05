cmake_minimum_required(VERSION 3.14)

project(taskBank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/win")

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Svg)
find_package(SQLite3 REQUIRED)

find_path(HPDF_INCLUDE_DIR
    NAMES hpdf.h
    PATHS
    /usr/local/include
    /usr/include
    /opt/homebrew/include  # Для Apple Silicon
)

find_library(HPDF_LIBRARY
    NAMES hpdf
    PATHS
    /usr/local/lib
    /usr/lib
    /opt/homebrew/lib  # Для Apple Silicon
)

set(HPDF_INCLUDE_DIRS ${HPDF_INCLUDE_DIR})
set(HPDF_LIBRARIES ${HPDF_LIBRARY})

qt_standard_project_setup()
qt6_add_resources(RESOURCE_TARGET resources resources.qrc)
# сначала надо написать qrc_resources
#qt6_add_resources(RESOURCE_TARGET qrc_resources resources.qrc)
add_executable(taskBank main.cpp ${RESOURCE_TARGET})

qt_add_qml_module(taskBank
    URI path
    VERSION 1.0
    QML_FILES main.qml
        qml/Container.qml
        qml/AddProjectWindow.qml
        qml/ProjectEditorWindow.qml
        qml/ConfirmationWindow.qml
        qml/TabsRow.qml
        qml/TaskEditor.qml
        qml/TagsRow.qml
        qml/TagsWindow.qml
        qml/AddTagWindow.qml
        qml/GenerateVariantsWindow.qml
        qml/CheckboxList.qml
        qml/VariantContent.qml
        qml/ProjectsWindow.qml
    RESOURCES resources.qrc
    SOURCES
        nlohmann/json.hpp
        repositories/ControlWorksRepository.h
        repositories/ControlWorksRepository.cpp
        models/controlwork.h
        component/controlworkscomponent.h
        component/controlworkscomponent.cpp
        repositories/controlworkeditorrepository.cpp
        models/task.h
        Constants.h
        databases/controlworkdatabase.h
        databases/controlworkdatabase.cpp
        utils/controlworkmetadataeditor.h
        utils/controlworkmetadataeditor.cpp
        models/taskgroup.h
        databases/controlworkcontentdatabase.h
        databases/controlworkcontentdatabase.cpp
        component/controlworkeditorcomponent.h
        component/controlworkeditorcomponent.cpp
        component/utils/TaskGroupsModel.h
        component/utils/TaskTabsModel.h
        component/utils/tasktagsmodel.h
        component/utils/variantsModel.h
        component/utils/groupDetailsModel.h
        models/Tag.h
        component/utils/AttachmentSaver.cpp
        component/utils/AttachmentSaver.h
        component/utils/CheckBoxListModel.h
        utils/controlworkpdfexporter.h
        utils/controlworkpdfexporter.cpp
        models/Variant.h
)

target_link_libraries(taskBank
    PRIVATE Qt6::Quick Qt6::Svg
)
target_link_libraries(taskBank
    PRIVATE SQLite::SQLite3 ${HPDF_LIBRARIES}
)

target_include_directories(taskBank
    PRIVATE ${HPDF_INCLUDE_DIRS}
)

include(GNUInstallDirs)
install(TARGETS taskBank
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
