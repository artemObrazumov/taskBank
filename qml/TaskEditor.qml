import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import Qt.labs.platform 1.1 as Platform
import "."
import utils.taskTagsModel
import utils.attachmentSaver

Rectangle {
    id: root
    color: "transparent"
    height: taskTitle.height + taskTitleRect.height + tagsTitle.height + tagsContainer.height + answerTitle.height + taskAnswerRect.height + saveButton.height
            + attachmentTitle.height + attachmentContainer.height + attachmentButton.height + 124

    property string path: ""
    property int taskId: -1
    property string attachmentPath: ""
    property alias content: taskTitleField.text
    property alias answer: taskAnswerField.text
    property TaskTagsModel tagsModel: TaskTagsModel {}

    signal saveClicked
    signal tagsSelectWindowOpened
    signal taskTagDeleted(int tagId)

    Text {
        id: taskTitle
        text: "Введите название задания"
        font.family: "Montserrat"
        font.pixelSize: 14
        color: "white"
    }

    Rectangle {
        id: taskTitleRect
        anchors.top: taskTitle.bottom
        anchors.left: root.left
        anchors.right: root.right
        anchors.topMargin: 8
        anchors.rightMargin: 16
        height: 188
        radius: 6
        color: "#374151"
        border.color: "#4B5563"
        border.width: 2
        z: 1

        ScrollView {
            width: parent.width
            height: 180

            TextArea {
                id: taskTitleField
                width: parent.width
                placeholderText: "Введите название"
                font.family: montserratMedium.name
                font.weight: 500
                font.pointSize: 16
                background: null
                wrapMode: Text.Wrap
                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.leftMargin: 8
                height: 180

                onActiveFocusChanged: {
                    taskTitleRect.border.color = activeFocus ? "#4680FF" : "#4B5563";
                }
            }
        }
    }

    Text {
        id: attachmentTitle
        text: "Приложение"
        font.family: "Montserrat"
        font.pixelSize: 14
        color: "white"
        anchors.top: taskTitleRect.bottom
        anchors.topMargin: 24
    }

    Rectangle {
        id: attachmentContainer
        //height: attachmentPath !== "" ? 250 : 0
        height: 250
        width: parent.width / 2
        color: "#1F2937"
        border.color: "#374151"
        border.width: 1
        radius: 5
        anchors.top: attachmentTitle.bottom
        anchors.topMargin: 8
        //visible: attachmentPath !== ""

        Image {
            id: photoImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "file://" + root.path + "/attachment/" + root.taskId
        }
    }

    Platform.FileDialog {
        id: attachmentDialog
        title: "Выбор картинки"
        folder: Platform.StandardPaths.writableLocation(Platform.StandardPaths.PicturesLocation)
        nameFilters: ["Изображения (*.png *.jpg *.jpeg)"]
        onAccepted: {
            var sourcePath = attachmentDialog.file.toString().replace("file://", "")
            attachmentSaver.saveImageToAppDir(sourcePath)
        }
    }

    AttachmentSaver {
        id: attachmentSaver
        onImageSaved: {
            var oldSource = photoImage.source;
            photoImage.source = "";
            photoImage.source = oldSource;
        }
        taskId: root.taskId
        path: root.path
    }

    Rectangle {
        id: attachmentButton
        color: bgColor
        radius: 8
        anchors.top: attachmentContainer.bottom
        anchors.left: root.left
        anchors.topMargin: 16
        width: attachmentText.width + 32
        height: attachmentText.height + 16

        readonly property color unselectedColor: "#1F2937"
        readonly property color selectedColor: "#253347"
        property color bgColor: unselectedColor

        Text {
            id: attachmentText
            text: "Изменить приложение"
            color: "#fff"
            font.family: "Montserrat"
            font.pixelSize: 16
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.topMargin: 8
        }

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
                attachmentDialog.open()
            }
        }
    }

    Text {
        id: tagsTitle
        text: "Категории"
        font.family: "Montserrat"
        font.pixelSize: 14
        color: "white"
        anchors.top: attachmentButton.bottom
        anchors.topMargin: 24
    }

    Rectangle {
        id: tagsContainer
        anchors.top: tagsTitle.bottom
        anchors.topMargin: 8
        width: parent.width
        height: tagAddButton.height
        color: "transparent"

        TagsRow {
            anchors.left: parent.left
            anchors.right: tagAddButton.left
            anchors.rightMargin: 8
            model: root.tagsModel

            onTagDeleted: function(tagId) {
                taskTagDeleted(tagId)
            }
        }

        Container {
            id: tagAddButton
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 18
            anchors.bottomMargin: 20
            implicitWidth: 40
            implicitHeight: 40
            color: bgColor

            readonly property color unselectedColor: "#2563EB"
            readonly property color selectedColor: "#4680FF"
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
                    tagsSelectWindowOpened()
                }
            }

            Image {
                id: plusImage
                width: 24
                height: 36
                source: "qrc:/image/plus.svg"
                anchors.centerIn: parent
            }
        }
    }

    Text {
        id: answerTitle
        text: "Ответ"
        font.family: "Montserrat"
        font.pixelSize: 14
        color: "white"
        anchors.top: tagsContainer.bottom
        anchors.topMargin: 24
    }

    Rectangle {
        id: taskAnswerRect
        anchors.top: answerTitle.bottom
        anchors.left: root.left
        anchors.right: root.right
        anchors.topMargin: 8
        anchors.rightMargin: 16
        height: 188
        radius: 6
        color: "#374151"
        border.color: "#4B5563"
        border.width: 2
        z: 1

        ScrollView {
            width: parent.width
            height: 180

            TextArea {
                id: taskAnswerField
                width: parent.width
                placeholderText: "Введите ответ"
                font.family: montserratMedium.name
                font.weight: 500
                font.pointSize: 16
                background: null
                wrapMode: Text.Wrap
                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.leftMargin: 8

                onActiveFocusChanged: {
                    taskAnswerRect.border.color = activeFocus ? "#4680FF" : "#4B5563";
                }
            }
        }
    }

    Rectangle {
        id: saveButton
        color: bgColor
        radius: 8
        anchors.top: taskAnswerRect.bottom
        anchors.right: root.right
        anchors.topMargin: 16
        anchors.rightMargin: 24
        width: saveText.width + 32
        height: saveText.height + 16

        readonly property color unselectedColor: "#1F2937"
        readonly property color selectedColor: "#253347"
        property color bgColor: unselectedColor

        Text {
            id: saveText
            text: "Сохранить"
            color: "#fff"
            font.family: "Montserrat"
            font.pixelSize: 16
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.topMargin: 8
        }

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
                saveClicked()
            }
        }
    }
}
