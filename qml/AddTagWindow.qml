import QtQuick 2.15

Window {
    id: tagsWindow
    visible: false
    width: 450
    height: 250
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
    }
}
