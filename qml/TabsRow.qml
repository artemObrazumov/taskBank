import QtQuick 2.15

ListView {
    id: tabs
    orientation: ListView.Horizontal
    spacing: 10
    clip: true
    width: parent.width
    height: realHeight

    property int selectedTaskId: -1
    property int realHeight: 0

    delegate: Rectangle {
        id: tab
        width: 240
        color: bgColor
        height: title.height + 16
        radius: 4

        readonly property color unselectedColor: "#2B384A"
        readonly property color selectedColor: "#3F5067"
        property color bgColor: unselectedColor

        Text {
            id: title
            text: model.tabData.taskId + " aioghejinfijfnvaejfnvajefa;ji"
            width: tab.width - 32
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.top: parent.top
            anchors.topMargin: 8
            font.pixelSize: 16
            font.family: montserratRegular.name
            font.weight: 500
            elide: Text.ElideRight
            color: if (model.tabData.taskId === selectedTaskId) { "#fff" } else { "#9CA3AF" }
        }

        Component.onCompleted: {
            tabs.realHeight = tab.height;
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
                tabClicked(model.tabData.taskId);
            }
        }
    }

    signal tabClicked(int taskId)
}
