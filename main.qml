import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import components.controlWorks
import "qml"

ApplicationWindow {
    visible: true
    width: 1200
    height: 700
    title: "контрольные работы"
    color: "#111827"

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

    FontLoader {
        id: montserratBold
        source: "qrc:/font/Montserrat-Bold.ttf"
    }

    property bool isAddProjectWindowOpened: false

    Rectangle {
        id: overlay
        anchors.fill: parent
        color: "#000"
        opacity: 0.5
        z: 100
        visible: isAddProjectWindowOpened
    }

    ColumnLayout {
        anchors.fill: parent

        Item {
            visible: repository.test.length > 0
            Layout.fillWidth: true
            Layout.fillHeight: true

            Flickable {
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: contentColumn.height + 80

                ColumnLayout {
                    id: contentColumn
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Rectangle {
                        color: "#1F2937"
                        Layout.fillWidth: true
                        implicitHeight: controlWorksTitle.height + 32 + 1

                        Item {
                            anchors.fill: parent
                            anchors.margins: 16

                            Text {
                                id: controlWorksTitle
                                text: "Контрольные работы"
                                color: "#fff"
                                font.family: montserratBold.name
                                font.pixelSize: 28
                                font.bold: true
                            }
                        }

                        Rectangle {
                            color: "#253347"
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            height: 1
                        }
                    }

                    GridLayout {
                        id: sidebarGrid
                        width: contentColumn.width
                        Layout.margins: 18
                        columns: requiredColumns
                        columnSpacing: 18
                        rowSpacing: 18

                        readonly property int requiredColumns: 3
                        property int itemWidth: (contentColumn.width - 36 - 36 - 120) / 3

                        Repeater {
                            model: repository.test

                            Container {
                                implicitWidth: sidebarGrid.itemWidth + 40
                                implicitHeight: workContent.height
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                                Item {
                                    id: workContent
                                    height: workContentColumn.height + 40
                                    anchors.top: parent.top
                                    anchors.right: parent.right
                                    anchors.left: parent.left
                                    anchors.margins: 20

                                    Rectangle {
                                        anchors.top: parent.top
                                        anchors.right: parent.right
                                        anchors.rightMargin: 12

                                        Image {
                                            source: "qrc:/image/cross.svg"
                                        }

                                        MouseArea {
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            cursorShape: Qt.PointingHandCursor
                                        }
                                    }

                                    ColumnLayout {
                                        id: workContentColumn

                                        Text {
                                            id: title
                                            text: modelData.title
                                            font.family: montserratMedium.name
                                            font.weight: 700
                                            font.pixelSize: 18
                                            Layout.bottomMargin: 12
                                            Layout.preferredWidth: sidebarGrid.itemWidth - 36
                                            elide: Text.ElideRight
                                            color: "#fff"
                                        }
                                        Text {
                                            opacity: if (modelData.isValid) {1} else {0}
                                            text: "Последнее изменение: " + modelData.lastEdited
                                            font.family: montserratRegular.name
                                            font.pixelSize: 16
                                            font.weight: 500
                                            Layout.bottomMargin: 12
                                            color: "#9CA3AF"
                                        }
                                        RowLayout {
                                            opacity: if (modelData.isValid) {1} else {0}
                                            Image {
                                                source: "qrc:/image/tasks.svg"
                                                Layout.rightMargin: 6
                                            }
                                            Text {
                                                text: "Заданий: " + modelData.tasks
                                                font.family: montserratRegular.name
                                                font.pixelSize: 16
                                                font.weight: 500
                                                color: "#D1D5DB"
                                                Layout.rightMargin: 18
                                            }
                                            Image {
                                                source: "qrc:/image/variants.svg"
                                                Layout.rightMargin: 6
                                            }
                                            Text {
                                                text: "Вариантов: " + modelData.variants
                                                font.family: montserratRegular.name
                                                font.pixelSize: 16
                                                font.weight: 500
                                                color: "#D1D5DB"
                                            }
                                        }
                                    }
                                    Text {
                                        visible: !modelData.isValid
                                        text: "Ошибка: проект поврежден"
                                        font.family: montserratRegular.name
                                        font.pixelSize: 16
                                        font.weight: 500
                                        anchors.bottom: parent.bottom
                                        anchors.bottomMargin: 40
                                        color: "red"
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            visible: repository.test.length === 0
            height: bookImage.height + noWorksText.height + 32
            Layout.alignment: Qt.AlignCenter
            color: "#fff"
            Image {
                id: bookImage
                source: "qrc:/image/openedbook.svg"
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: noWorksText
                text: "Нет контрольных работ."
                font.family: montserratMedium.name
                font.weight: 600
                font.pointSize: 24
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#6B7280"
            }
        }
    }

    Container {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 18
        anchors.bottomMargin: 20
        implicitWidth: 64
        implicitHeight: 64
        color: bgColor

        readonly property color unselectedColor: "#2563EB"
        readonly property color selectedColor: "#4680FF"
        property color bgColor: unselectedColor

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
                newProjectWindow.show();
                isAddProjectWindowOpened = true;
            }
        }

        Image {
            id: plusImage
            width: 32
            height: 48
            source: "qrc:/image/plus.svg"
            anchors.centerIn: parent
        }
    }

    AddProjectWindow {
        id: newProjectWindow
        onWindowClosed: {
            isAddProjectWindowOpened = false;
        }
    }

    ProjectEditorWindow {

    }
}
