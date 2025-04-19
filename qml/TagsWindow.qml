import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import components.controlWorks
import utils.taskTagsModel

Window {
    id: tagsWindow
    visible: false
    width: 350
    height: 600
    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    color: "transparent"

    FontLoader {
        id: montserratRegular
        source: "qrc:/font/Montserrat-Regular.ttf"
    }

    FontLoader {
        id: montserratMedium
        source: "qrc:/font/Montserrat-Medium.ttf"
    }

    property TaskTagsModel tagsModel: TaskTagsModel {}

    signal tagSelected(int tagId)
    signal cancelled()

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#1F2937"
        radius: 8

        anchors.fill: parent

        Text {
            id: titleText
            text: "Добавить категорию"
            font.pointSize: 18
            font.family: montserratMedium.name
            font.weight: 700
            Layout.alignment: Qt.AlignTop
            width: parent.width
            wrapMode: Text.Wrap
            color: "#fff"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
        }

        ListView {
            id: tagsList
            model: tagsModel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: titleText.bottom
            anchors.topMargin: 8
            height: tagsWindow.height - titleText.height - cancelButton.height - 32
            clip: true
            delegate: Rectangle {
                width: tagsList.width
                height: tagTitle.height + 24
                color: bgColor
                radius: 10
                Text {
                    id: tagTitle
                    text: model.tagData.title
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    anchors.centerIn: parent
                    anchors.margins: 12
                    color: "#fff"
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
                        tagSelected(model.tagData.tagId)
                    }
                }
            }
        }

        Rectangle {
            id: cancelButton
            color: bgColor
            radius: 8
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 20

            readonly property color unselectedColor: "#4B5563"
            readonly property color selectedColor: "#606873"
            property color bgColor: unselectedColor

            width: cancelButtonText.width + 32
            height: cancelButtonText.height + 16

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
                    cancelled()
                }
            }

            Text {
                id: cancelButtonText
                text: "Отмена"
                font.family: montserratRegular.name
                font.pointSize: 16
                font.weight: 400
                color: "#fff"
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: addButton
            color: bgColor
            radius: 8
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 20
            anchors.bottomMargin: 20

            readonly property color unselectedColor: "#4B5563"
            readonly property color selectedColor: "#606873"
            property color bgColor: unselectedColor

            width: addButtonText.width + 32
            height: addButtonText.height + 16

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
                    addTagWindow.show()
                }
            }

            Text {
                id: addButtonText
                text: "Создать"
                font.family: montserratRegular.name
                font.pointSize: 16
                font.weight: 400
                color: "#fff"
                anchors.centerIn: parent
            }
        }
    }

    AddTagWindow {
        id: addTagWindow
        visible: false
    }
}
