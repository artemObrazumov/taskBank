import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    ScrollView {
        anchors.fill: parent

        Text {
            text: "Вариант " + root.id
            font.family: montserratBold.name
            font.pointSize: 20
            font.weight: 700
            anchors.top: parent.top
            anchors.left: parent.left
        }

        ListView {
            id: tasksList
            model: groups

            delegate: Item {
                text:
            }
        }
    }
}
