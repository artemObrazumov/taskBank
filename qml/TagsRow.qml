import QtQuick 2.15
import utils.taskTagsModel

ListView {
    id: tags
    orientation: ListView.Horizontal
    spacing: 10
    clip: true
    width: parent.width
    height: 200

    property int realHeight: 0

    signal tagDeleted(int tagId)

    delegate: Rectangle {
        id: tag
        width: 180
        color: bgColor
        height: title.height + 16
        radius: 16

        readonly property color unselectedColor: "#2B384A"
        readonly property color selectedColor: "#3F5067"
        property color bgColor: unselectedColor

        Text {
            id: title
            text: model.tagData.title
            width: tag.width - 32
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            font.pixelSize: 14
            font.family: montserratRegular.name
            font.weight: 500
            elide: Text.ElideRight
            color: "#fff"
        }

        Component.onCompleted: {
            tags.realHeight = tag.height;
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
                    tagDeleted(model.tagData.tagId);
                }
            }
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
        }
    }
}
