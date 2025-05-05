import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import components.controlWorks
import "."

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 700
    color: "#111827"
    title: "Контрольные работы"

    StackView {
        id: stackView
        initialItem: ProjectsWindow {
            onWorkOpened: function(id) {
                stackView.push(Qt.resolvedUrl("qml/ProjectEditorWindow.qml"), {"workId": id})
                root.title = "Редактор контрольной работы"
            }
        }
        anchors.fill: parent
    }
}
