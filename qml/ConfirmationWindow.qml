import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import components.controlWorks

Window {
    property string message: ""

    id: confirmationWindow
    visible: false
    width: 450
    height: 160
    title: title
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

    signal accepted()
    signal cancelled()

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#1F2937"
        radius: 8

        anchors.fill: parent

        Text {
            id: titleText
            text: confirmationWindow.message
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
                    accepted()
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
