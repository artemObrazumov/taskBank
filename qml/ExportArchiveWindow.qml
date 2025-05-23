import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import components.controlWorks

Window {
    id: exportProjectWindow
    visible: false
    width: 650
    height: 240
    title: "Экспорт контрольной работы"
    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    color: "transparent"

    signal windowClosed(int id, string path)

    property int workId: -1
    property string path: ""

    property int dragX: 0
    property int dragY: 0

    MouseArea {
        id: dragArea
        anchors.fill: parent

        onPressed: {
            dragX = mouse.x;
            dragY = mouse.y;
        }

        onPositionChanged: {
            exportProjectWindow.x += mouse.x - dragX;
            exportProjectWindow.y += mouse.y - dragY;
        }
    }

    ControlWorksComponent {
        id: repository
    }

    FontLoader {
        id: montserratRegular
        source: "qrc:/font/Montserrat-Regular.ttf"
    }

    FontLoader {
        id: montserratMedium
        source: "qrc:/font/Montserrat-Medium.ttf"
    }

    FileDialog {
        id: saveDialog
        title: "Сохранить архив"
        fileMode: FileDialog.SaveFile
        nameFilters: ["ZIP files (*.zip)"]
        defaultSuffix: "zip"

        onAccepted: {
            exportProjectWindow.path = selectedFile.toString().replace(/^file:\/\//, "")
            fileText.text = exportProjectWindow.path
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#1F2937"
        radius: 8

        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20

            Text {
                id: titleText
                text: "Экспорт контрольной работы"
                font.pointSize: 20
                font.family: montserratMedium.name
                font.weight: 700
                Layout.alignment: Qt.AlignTop
                width: parent.width
                color: "#fff"
            }

            Item {
                height: 12
            }

            Text {
                id: folderTitle
                text: "Выберите место"
                font.family: montserratMedium.name
                font.pointSize: 14
                font.weight: 500
                color: "#D1D5DB"
            }

            Rectangle {
                id: folderBorder
                Layout.fillWidth: true
                height: fileSelectButton.height + 20
                radius: 6
                color: "#374151"
                border.color: "#4B5563"
                border.width: 2

                Text {
                    id: fileText
                    font.family: montserratMedium.name
                    font.weight: 500
                    font.pointSize: 16
                    color: "#fff"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: fileSelectButton.left
                    elide: Text.ElideLeft
                    anchors.leftMargin: 10
                }

                Rectangle {
                    id: fileSelectButton
                    color: bgColor
                    radius: 8
                    anchors.topMargin: 10
                    anchors.rightMargin: 10
                    anchors.top: parent.top
                    anchors.right: parent.right

                    readonly property color unselectedColor: "#4B5563"
                    readonly property color selectedColor: "#606873"
                    property color bgColor: unselectedColor

                    width: selectButtonText.width + 32
                    height: selectButtonText.height + 16

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
                            saveDialog.open()
                        }
                    }

                    Text {
                        id: selectButtonText
                        text: "Выбрать"
                        font.family: montserratRegular.name
                        font.pointSize: 16
                        font.weight: 400
                        color: "#fff"
                        anchors.centerIn: parent
                    }
                }
            }

            Item {
                height: 12
            }

            Row {
                id: buttonsRow
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                width: parent.width
                spacing: 12

                Rectangle {
                    color: bgColor
                    radius: 8
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    Layout.topMargin: 8
                    Layout.bottomMargin: 8

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
                            windowClosed(-1, "")
                            exportProjectWindow.close()
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

                Rectangle {
                    color: bgColor
                    radius: 8
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    Layout.topMargin: 8
                    Layout.bottomMargin: 8

                    readonly property color unselectedColor: "#2563EB"
                    readonly property color selectedColor: "#4680FF"
                    property color bgColor: unselectedColor

                    width: applyButtonText.width + 32
                    height: applyButtonText.height + 16

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
                            windowClosed(exportProjectWindow.workId, exportProjectWindow.path)
                            exportProjectWindow.close()
                        }
                    }

                    Text {
                        id: applyButtonText
                        font.family: montserratRegular.name
                        font.pointSize: 16
                        font.weight: 400
                        text: "Экспорт"
                        color: "#fff"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
