import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: wrapper
    Layout.fillWidth: true
    color: bgColor
    radius: 8

    readonly property color unselectedColor: "#1F2937"
    readonly property color selectedColor: "#253347"
    property color bgColor: unselectedColor

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onEntered: {
            bgColor = selectedColor;
        }

        onExited: {
            bgColor = unselectedColor;
        }
    }
}
