import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: tagsWindow
    visible: false
    width: 450
    height: 200
    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    color: "transparent"

    signal accepted(string name)
    signal cancelled()

    FontLoader {
        id: montserratRegular
        source: "qrc:/font/Montserrat-Regular.ttf"
    }

    FontLoader {
        id: montserratMedium
        source: "qrc:/font/Montserrat-Medium.ttf"
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#1F2937"
        radius: 8

        anchors.fill: parent

        Text {
            id: titleText
            text: "Создать категорию"
            font.pointSize: 18
            font.family: montserratMedium.name
            font.weight: 700
            width: parent.width
            wrapMode: Text.Wrap
            color: "#fff"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
        }

        Text {
            id: tagNameTitle
            text: "Название категории"
            font.family: montserratMedium.name
            font.pointSize: 14
            font.weight: 500
            anchors.top: titleText.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.topMargin: 16
            color: "#D1D5DB"
        }

        Rectangle {
            id: borderRect
            width: parent.width
            height: tagNameField.height + 12
            radius: 6
            anchors.top: tagNameTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 8
            color: "#374151"
            border.color: "#4B5563"
            border.width: 2

            TextField {
                id: tagNameField
                anchors.fill: parent
                placeholderText: "Введите название"
                font.family: montserratMedium.name
                font.weight: 500
                font.pointSize: 16
                background: null
                anchors.topMargin: 8
                anchors.leftMargin: 8

                onActiveFocusChanged: {
                    borderRect.border.color = activeFocus ? "#4680FF" : "#4B5563";
                }
            }
        }

        Rectangle {
            id: acceptButton
            color: bgColor
            radius: 8
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 20

            readonly property color unselectedColor: "#4B5563"
            readonly property color selectedColor: "#606873"
            property color bgColor: unselectedColor

            width: acceptButtonText.width + 32
            height: acceptButtonText.height + 16

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
                    accepted(tagNameField.text)
                }
            }

            Text {
                id: acceptButtonText
                text: "Ок"
                font.family: montserratRegular.name
                font.pointSize: 16
                font.weight: 400
                color: "#fff"
                anchors.centerIn: parent
            }
        }

        Rectangle {
            color: bgColor
            radius: 8
            anchors.right: acceptButton.left
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
    }
}
