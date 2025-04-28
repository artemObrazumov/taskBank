import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import utils.groupDetailsModel

Column {
    id: root
    spacing: 12

    property GroupDetailsModel groups: GroupDetailsModel {}
    property int variantId: -1
    property string path: ""

    Text {
        id: variantTitle
        text: "Вариант " + root.variantId
        font.family: montserratBold.name
        font.pointSize: 20
        font.weight: 700
        color: "#fff"
    }

    Repeater {
        id: tasksList
        model: root.groups

        delegate: Column {
            spacing: 12

            Text {
                text: "Задание №" + model.variant.index
                font.family: montserratBold.name
                font.pointSize: 16
                font.weight: 700
                color: "#fff"
                Layout.topMargin: 16
            }
            Rectangle {
                id: attachmentContainer
                height: 250
                width: root.width / 2
                color: "#1F2937"
                border.color: "#374151"
                border.width: 1
                radius: 5

                Image {
                    id: photoImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: "file://" + root.path + "/attachment/" + model.variant.taskId
                    cache: false
                }
            }
            Text {
                text: model.variant.taskContent
                font.pointSize: 14
                color: "#fff"
                Layout.topMargin: 8
            }
            Text {
                text: "Ответ: " + model.variant.taskAnswer
                font.pointSize: 14
                color: "#fff"
                Layout.topMargin: 8
            }
        }
    }
}
