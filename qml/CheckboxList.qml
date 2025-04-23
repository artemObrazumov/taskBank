import QtQuick 2.15

ListView {
    spacing: 10
    clip: true

    signal checked(int id)

    delegate: Rectangle {
        color: if (model.checkboxData.checked) { "#4B5563" } else { "transparent" }
        radius: 8

        width: parent.width
        height: applyButtonText.height + 16

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                checked(model.checkboxData.id)
            }
        }

        Text {
            id: applyButtonText
            font.family: montserratRegular.name
            font.pointSize: 16
            font.weight: 400
            text: model.checkboxData.title
            color: if (model.checkboxData.checked) { "#fff" } else { "#606873" }
            anchors.centerIn: parent
        }
    }
}
