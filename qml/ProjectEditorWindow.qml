import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components.controlWorkEditor
import QtQuick.Dialogs
import "."

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 700
    title: "Редактор контрольных работ"
    color: "#111827"

    property int tab: 0
    property int selectedTaskId: -1
    property int selectedVariantId: -1

    property bool isGenerateVariantsWindowOpened: false

    ControlWorkEditorComponent {
        id: editorComponent
        workId: 2

        onTaskOpened: function(content, answer) {
            taskEditor.content = content;
            taskEditor.answer = answer;
        }

        onTaskDeleted: function(taskId) {
            if (selectedTaskId === taskId) {
                selectedTaskId = -1;
            }
        }
    }

    FontLoader {
        id: montserratRegular
        source: "qrc:/font/Montserrat-Regular.ttf"
    }

    FontLoader {
        id: montserratMedium
        source: "qrc:/font/Montserrat-Medium.ttf"
    }

    Rectangle {
        id: overlay
        anchors.fill: parent
        color: "#000"
        opacity: 0.5
        z: 100
        visible: isGenerateVariantsWindowOpened
    }

    Rectangle {
        id: navigationSection
        width: parent.width * 0.3
        height: parent.height
        color: "#1F2937"

        Rectangle {
            id: header
            width: parent.width
            height: workTitle.height + 32
            color: "transparent"
            Text {
                id: workTitle
                width: parent.width
                color: "#fff"
                font.family: montserratMedium.name
                font.pointSize: 18
                font.weight: 700
                text: editorComponent.controlWork.title
                elide: Text.ElideRight
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 16
            }
        }

        Row {
            id: tabsBlock
            anchors.top: header.bottom
            width: parent.width - 32
            anchors.left: parent.left
            anchors.leftMargin: 16
            spacing: 16

            Rectangle {
                id: tasksTab
                width: parent.width / 2 - 8
                height: tasksText.height + 24
                color: bgColor
                radius: 10
                Text {
                    id: tasksText
                    text: "Задания"
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    anchors.margins: 12
                    anchors.centerIn: parent
                    color: if (tab == 0) { "#fff" } else { "#9CA3AF" }
                }

                readonly property color unselectedColor: "transparent"
                readonly property color selectedColor: "#2B384A"
                property color bgColor: selectedColor

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onEntered: {
                        parent.bgColor = parent.selectedColor;
                    }

                    onExited: {
                        if (tab == 0) return;
                        parent.bgColor = parent.unselectedColor;
                    }

                    onClicked: {
                        tab = 0;
                        varinatsTab.bgColor = varinatsTab.unselectedColor;
                        variantsContainer.visible = false;
                        tasksListContainer.visible = true;
                    }
                }
            }

            Rectangle {
                id: varinatsTab
                width: parent.width / 2 - 8
                height: variantsText.height + 24
                color: bgColor
                radius: 10
                Text {
                    id: variantsText
                    text: "Варианты"
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    anchors.centerIn: parent
                    anchors.margins: 12
                    color: if (tab == 1) { "#fff" } else { "#9CA3AF" }
                }

                readonly property color unselectedColor: "transparent"
                readonly property color selectedColor: "#2B384A"
                property color bgColor: unselectedColor

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onEntered: {
                        parent.bgColor = parent.selectedColor;
                    }

                    onExited: {
                        if (tab == 1) return;
                        parent.bgColor = parent.unselectedColor;
                    }

                    onClicked: {
                        tab = 1;
                        tasksTab.bgColor = tasksTab.unselectedColor;
                        tasksListContainer.visible = false;
                        variantsContainer.visible = true;
                    }
                }
            }
        }

        Rectangle {
            id: tasksListContainer
            y: header.height + varinatsTab.height + 16
            width: parent.width
            height: parent.height - addTaskBlock.height - header.height - tabsBlock.height - 32
            color: "transparent"

            ListView {
                anchors.fill: parent
                model: editorComponent.taskGroups
                clip: true
                delegate: Item {
                    width: tasksListContainer.width
                    height: column.height + 8

                    Column {
                        id: column
                        width: parent.width
                        Rectangle {
                            id: taskContainer
                            width: parent.width - 16
                            height: taskTitle.height + 16
                            x: 8
                            radius: 4
                            color: "transparent"

                            Row {
                                height: taskTitle.height + 16
                                anchors.left: parent.left
                                anchors.leftMargin: 8
                                spacing: 10

                                Image {
                                    id: taskIndicator
                                    source: "qrc:/image/openIndicator.svg"
                                    rotation: if (model.groupData.show === true) { 0 } else { -90 }
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Text {
                                    id: taskTitle
                                    text: "Задание " + model.groupData.index
                                    font.family: montserratRegular.name
                                    font.weight: 500
                                    font.pointSize: 16
                                    color: if (model.groupData.show) { "#fff" } else { "#6B7280" }
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                            Image {
                                id: taskAddButton
                                source: "qrc:/image/plus.svg"
                                anchors.right: parent.right
                                anchors.rightMargin: 8
                                anchors.verticalCenter: parent.verticalCenter
                                z: 2
                                MouseArea {
                                    width: parent.width
                                    height: parent.height
                                    cursorShape: Qt.PointingHandCursor

                                    onClicked: {
                                        editorComponent.addTaskToGroup(model.groupData.id);
                                    }
                                }
                            }
                            MouseArea {
                                width: parent.width
                                height: parent.height
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                z: 1

                                onEntered: {
                                    parent.color = "#2B384A";
                                }

                                onExited: {
                                    if (model.groupData.show === true) return;
                                    parent.color = "transparent";
                                }

                                onClicked: {
                                    editorComponent.taskGroups.toggleGroupShow(model.groupData.id);
                                }
                            }
                        }

                        Item {
                            width: parent.width
                            height: 8
                            visible: model.groupData.show
                        }

                        Item {
                            width: parent.width
                            height: noTasksText.height
                            visible: model.groupData.show && model.groupData.taskVariants.length === 0

                            Text {
                                id: noTasksText
                                text: "Нет заданий"
                                font.family: montserratRegular.name
                                font.weight: 500
                                font.pointSize: 16
                                anchors.margins: 12
                                anchors.centerIn: parent
                                color: "#fff"
                            }
                        }

                        property var groupData: model.groupData

                        Repeater {
                            id: taskVariantsList
                            model: parent.groupData.taskVariants
                            Layout.topMargin: 8
                            delegate: Rectangle {
                                width: parent.width + 16
                                height: taskVariantTitle.height + 16
                                visible: parent.groupData.show
                                radius: 4
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.leftMargin: 8 + 24
                                anchors.rightMargin: 8
                                color: "transparent"

                                Text {
                                    id: taskVariantTitle
                                    text: modelData.content ? modelData.content : "Нет названия"
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    anchors.margins: 8
                                    anchors.top: parent.top
                                    font.family: montserratRegular.name
                                    font.weight: 500
                                    font.pointSize: 16
                                    color: if (selectedTaskId === modelData.taskId) { "#fff" } else { "#6B7280" }
                                }

                                Image {
                                    source: "qrc:/image/cross.svg"
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: parent.right
                                    anchors.rightMargin: 8
                                    z: 4

                                    MouseArea {
                                        width: parent.width
                                        height: parent.height
                                        cursorShape: Qt.PointingHandCursor

                                        onClicked: {
                                            confirmationWindow.show();
                                        }
                                    }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    z: 3

                                    onEntered: {
                                        parent.color = "#2B384A";
                                    }

                                    onExited: {
                                        parent.color = "transparent";
                                    }

                                    onClicked: {
                                        editorComponent.openTask(modelData.taskId);
                                        selectedTaskId = modelData.taskId;
                                        editorComponent.addTaskTab(modelData.taskId);
                                    }
                                }

                                ConfirmationWindow {
                                    id: confirmationWindow
                                    message: "Вы действительно хотите удалить это\nзадание?"

                                    onAccepted: {
                                        editorComponent.deleteTask(parent.groupData.id, modelData.taskId)
                                    }

                                    onCancelled: {
                                        confirmationWindow.hide()
                                    }
                                }
                            }
                        }

                        Item {
                            width: parent.width
                            height: 8
                            visible: show
                        }
                    }
                }
            }
        }

        Rectangle {
            visible: false
            id: variantsContainer
            y: header.height + varinatsTab.height + 16
            width: parent.width
            height: parent.height - addTaskBlock.height
            color: "transparent"
            clip: true

            ListView {
                anchors.fill: parent
                model: variantsModel
                delegate: Item {
                    width: parent.width
                    height: variantsColumn.height + 8

                    Column {
                        id: variantsColumn
                        width: parent.width
                        Rectangle {
                            id: variantItemContainer
                            width: parent.width - 16
                            height: variantTitle.height + 16
                            x: 8
                            radius: 4
                            color: "transparent"

                            Text {
                                id: variantTitle
                                text: title
                                font.family: montserratRegular.name
                                font.weight: 500
                                font.pointSize: 16
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.margins: 8
                                color: if (selectedVariantId == varId) { "#fff" } else { "#6B7280" }
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            MouseArea {
                                width: parent.width
                                height: parent.height
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                z: 1

                                onEntered: {
                                    parent.color = "#2B384A";
                                }

                                onExited: {
                                    parent.color = "transparent";
                                }

                                onClicked: {
                                    selectedVariantId = varId;
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: addTaskBlock
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            anchors.bottomMargin: 8
            height: addTaskRow.height
            color: bgColor
            radius: 10
            visible: tab == 0

            Row {
                id: addTaskRow
                height: addTaskTitle.height + 32
                anchors.left: parent.left
                anchors.leftMargin: 8
                spacing: 10

                Image {
                    source: "qrc:/image/plus.svg"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: addTaskTitle
                    text: "Добавить задание"
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    color: "#fff"
                    anchors.verticalCenter: parent.verticalCenter
                }

            }

            readonly property color unselectedColor: "transparent"
            readonly property color selectedColor: "#2B384A"
            property color bgColor: unselectedColor

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

                onEntered: {
                    parent.bgColor = parent.selectedColor;
                }

                onExited: {
                    parent.bgColor = parent.unselectedColor;
                }

                onClicked: {
                    editorComponent.addTaskGroup();
                }
            }
        }

        Rectangle {
            id: generateVariantsBlock
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            anchors.bottomMargin: 8
            height: generateVariantsRow.height
            color: bgColor
            radius: 10
            visible: tab == 1

            Row {
                id: generateVariantsRow
                height: generateVariantsTitle.height + 32
                anchors.left: parent.left
                anchors.leftMargin: 8
                spacing: 10

                Image {
                    source: "qrc:/image/plus.svg"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: generateVariantsTitle
                    text: "Cоздать варианты"
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    color: "#fff"
                    anchors.verticalCenter: parent.verticalCenter
                }

            }

            readonly property color unselectedColor: "transparent"
            readonly property color selectedColor: "#2B384A"
            property color bgColor: unselectedColor

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

                onEntered: {
                    parent.bgColor = parent.selectedColor;
                }

                onExited: {
                    parent.bgColor = parent.unselectedColor;
                }

                onClicked: {
                    editorComponent.loadTaskGroupCheckboxes()
                    editorComponent.loadTaskTagCheckboxes()
                    isGenerateVariantsWindowOpened = true
                    variantsWindow.show()
                }
            }
        }
    }

    Rectangle {
        id: navigationBorder
        width: 1
        height: parent.height
        color: "#374151"
        anchors.left: navigationSection.right
    }

    Rectangle {
        id: tabsRowContainer
        anchors.left: navigationBorder.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 16
        height: tabsRow.height
        color: "transparent"

        TabsRow {
            id: tabsRow
            model: editorComponent.taskTabs
            selectedTaskId: root.selectedTaskId

            onTabClicked: function(taskId) {
                editorComponent.saveLocally(selectedTaskId, taskEditor.content, taskEditor.answer);
                editorComponent.openTask(taskId);
                root.selectedTaskId = taskId;
            }

            onTabClosed: function(taskId) {
                editorComponent.closeTaskTab(taskId);
                if (root.selectedTaskId === taskId) {
                    root.selectedTaskId = -1;
                }
            }
        }
    }

    ScrollView {
        visible: selectedTaskId != -1
        anchors.top: tabsRowContainer.bottom
        anchors.left: navigationBorder.right
        anchors.topMargin: 16
        anchors.leftMargin: 8
        clip: true
        height: parent.height - tabsRowContainer.height - 48
        width: parent.width - navigationSection.width - 16
        contentHeight: taskEditor.height + 16

        Item {
            id: taskEditorWrapper
            width: parent.width
            height: taskEditor.height
            anchors.top: parent.top
            anchors.left: parent.left

            TaskEditor {
                id: taskEditor
                width: parent.width

                tagsModel: editorComponent.taskTags
                taskId: editorComponent.taskId
                path: editorComponent.path

                onSaveClicked: {
                    editorComponent.saveTask(selectedTaskId, taskEditor.content, taskEditor.answer)
                }

                onTagsSelectWindowOpened: {
                    editorComponent.loadTagsList()
                    tagsWindow.show()
                }

                onTaskTagDeleted: function(tagId) {
                    editorComponent.deleteTag(tagId)
                }
            }
        }
    }

    TagsWindow {
        id: tagsWindow
        visible: false

        tagsModel: editorComponent.tagsSelectList

        onCancelled: {
            tagsWindow.close()
        }

        onTagSelected: function (tagId) {
            tagsWindow.close()
            editorComponent.addTag(tagId)
        }

        onTagAdded: function(title) {
            editorComponent.createTag(title)
        }
    }

    GenerateVariantsWindow {
        id: variantsWindow
        visible: false
        taskGroupsModel: editorComponent.taskGroupsCheckboxList
        taskTagsModel: editorComponent.taskTagsCheckboxList

        onCancelled: {
            isGenerateVariantsWindowOpened = false
        }

        onCheckedGroup: function(id) {
            editorComponent.toggleGroupCheckbox(id)
        }

        onCheckedTag: function(id) {
            editorComponent.toggleTagCheckbox(id)
        }

        onCreateVariants: function(count) {
            editorComponent.generateVariants(count)
        }
    }

    Button {
        onClicked: {
            editorComponent.generateVariants()
        }
    }
}
